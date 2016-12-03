/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/31 19:06:28 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/03 17:14:52 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
	{
		return (color_add(c, color_mult(compute_light(refl, --iter_refl),
		(ray->obj_hit)->mater.int_refl)));
	}
	return (c);
}

t_color		compute_light_bis(t_data ray, int iter_refl, t_color c, int lights)
{
	if (ray.obj_hit->mater.int_trans > 0)
		c = color_stack(c, transparent_lighting(&ray, iter_refl,
			color_new(0, 0, 0)));
	if (ray.obj_hit->mater.int_refl > 0)
		c = color_stack(c, reflection_lighting(&ray, iter_refl,
			color_new(0, 0, 0)));
	c = color_mult(c, 1 / (float)lights);
	return (color_add(c, color_mult(get_texture(ray,
	ray.obj_hit->mater.tex), 0.2)));
}

t_color		compute_light(t_data ray, int iter_refl)
{
	t_color		c;
	t_light		*l;
	int			lights;
	float		coef;

	l = g_env.scene.lgt;
	c = color_new(0, 0, 0);
	lights = 0;
	ray.hit_point = vec_add(ray.orig, vec_mult(ray.dir, ray.solut));
	get_norm(&ray);
	if (ray.obj_hit->type == SKYBOX)
		return (get_texture(ray, ray.obj_hit->mater.tex));
	while (l)
	{
		coef = get_shadow(l, &ray);
		c = color_stack(c, color_mult(diffuse_lighting(&ray, l), coef));
		if (coef >= 0.75 && ray.obj_hit->mater.shiny != 0)
			c = color_stack(c, color_mult(specular_lighting(&ray, l), coef));
		l = l->next;
		lights++;
	}
	return (compute_light_bis(ray, iter_refl, c, lights));
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
