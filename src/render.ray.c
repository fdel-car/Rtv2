/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/31 19:06:28 by fdel-car          #+#    #+#             */
/*   Updated: 2016/11/25 15:29:11 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color		diffuse_lighting(t_data *ray, t_light *l)
{
	t_color	c;
	float	cos;

	c = color_new(0, 0, 0);
	if (l->type == POINT_L)
		ray->light = vec_norm(vec_sub(l->pos, ray->hit_point));
	if (l->type == DIR_L)
		ray->light = vec_mult(l->dir, -1);
	cos = vec_dotp(ray->light, ray->norm);
	if (cos > 0)
	{
		c = color_add(color_add(c, color_mult(l->color, l->intensity * cos))
		, color_mult(get_texture(*ray), l->intensity * cos));
	}
	return (c);
}

t_color		specular_lighting(t_data *ray, t_light *l)
{
	t_color	c;

	c = color_new(0, 0, 0);
	ray->refl = vec_norm(vec_add(ray->dir, vec_mult(ray->norm,
	-vec_dotp(ray->norm, ray->dir) * 2.0)));
	if (vec_dotp(ray->light, ray->refl) > 0
	&& vec_dotp(ray->light, ray->norm) > 0)
	{
		c = color_add(c, color_mult(l->color,
		powf(vec_dotp(ray->light, ray->refl), (ray->obj_hit)->mater.shiny)));
	}
	return (c);
}

gboolean	is_shadowed(t_light *l, t_data *ray)
{
	t_data sh;
	t_vect tmp;

	if (l->type == DIR_L)
	{
		sh.orig = ray->hit_point;
		sh.dir = vec_mult(l->dir, -1);
		sh = intersect_obj(sh, TRUE);
		if (sh.solut == -1)
			return (TRUE);
		return (FALSE);
	}
	sh.orig = l->pos;
	sh.dir = vec_norm(vec_sub(ray->hit_point, l->pos));
	sh = intersect_obj(sh, TRUE);
	if (sh.obj_hit == ray->obj_hit)
		return (TRUE);
	tmp = vec_add(sh.orig, vec_mult(sh.dir, sh.solut));
	if (dist_p(tmp, l->pos) < dist_p(ray->hit_point, l->pos) - EPSILON)
		return (FALSE);
	return (TRUE);
}

t_color		reflection_lighting(t_data *ray, int iter_refl, t_color c)
{
	t_data	refl;

	refl.dir = vec_mult(ray->norm, -2.0 * vec_dotp(ray->dir, ray->norm));
	refl.dir = vec_norm(vec_add(ray->dir, refl.dir));
	refl.orig = ray->hit_point;
	refl = intersect_obj(refl, FALSE);
	if (iter_refl > 0 && refl.solut != -1)
		return (color_add(c, color_mult(compute_light(refl, --iter_refl),
		(ray->obj_hit)->mater.int_refl)));
	return (c);
}

t_vect	refract_dir(t_data *ray, t_obj *obj)
{
	float	n;
	float	n1;
	float	n2;
	float	calc[3];
	t_vect	dir;

	calc[0] = vec_dotp(ray->norm, ray->dir);
	if (calc[0] > 0.0)
	{
		n1 = 1.0;
		n2 = obj->mater.indice;
		ray->norm = vec_mult(ray->norm, -1.0);
	}
	else
	{
		n1 = obj->mater.indice;
		n2 = 1.0;
		calc[0] = -calc[0];
	}
	n = n1 / n2;
	calc[2] = n * n * (1.0 - calc[0] * calc[0]);
	calc[1] = sqrt(1.0 - calc[2]);
	dir = vec_add(vec_mult(ray->dir, n),
	vec_mult(ray->norm, (n * calc[0] - calc[1])));
	return (vec_norm(dir));
}

t_color		transparent_lighting(t_data *ray, int iter_refl, t_color c)
{
	t_data	refr;

	refr.dir = refract_dir(ray, ray->obj_hit);
	refr.orig = ray->hit_point;
	refr = intersect_obj(refr, FALSE);
	if (refr.solut != -1)
		return (color_add(c, color_mult(compute_light(refr, iter_refl),
		(ray->obj_hit)->mater.int_trans)));
	return (c);
}

t_color		compute_light(t_data ray, int iter_refl)
{
	t_color		c;
	t_light		*l;
	gboolean	sh;
	int			lights;

	l = g_env.scene.lgt;
	c = color_new(0, 0, 0);
	lights = 0;
	ray.hit_point = vec_add(ray.orig, vec_mult(ray.dir, ray.solut));
	get_norm(&ray);
	if (ray.obj_hit->type == SKYBOX)
		return (get_texture(ray));
	while (l)
	{
		sh = is_shadowed(l, &ray);
		if (sh != FALSE)
		{
			c = color_stack(c, diffuse_lighting(&ray, l));
			if (ray.obj_hit->mater.shiny != 0)
				c = color_stack(c, specular_lighting(&ray, l));
		}
		l = l->next;
		lights++;
	}
	if (ray.obj_hit->mater.int_trans > 0)
		c = color_stack(c, transparent_lighting(&ray, iter_refl,
			color_new(0, 0, 0)));
	if (ray.obj_hit->mater.int_refl > 0)
		c = color_stack(c, reflection_lighting(&ray, iter_refl,
			color_new(0, 0, 0)));
	c = color_mult(c, 1 / (float)lights);
	return (color_add(c, color_mult(get_texture(ray), 0.2)));
}

t_color		render_ray(t_data ray)
{
	t_color color;

	if (ray.solut != -1 && ray.obj_hit)
		color = compute_light(ray, g_env.scene.iter_refl);
	else
		color = color_new(0, 0, 0);
	return (color);
}
