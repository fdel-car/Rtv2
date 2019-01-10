/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/31 19:06:28 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/14 16:23:10 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color		reflection_lighting(t_data *ray, int iter_refl, int iter_trans,
	t_color c)
{
	t_data	refl;

	refl.dir = vec_mult(ray->norm, -2.0 * vec_dotp(ray->dir, ray->norm));
	refl.dir = vec_norm(vec_add(ray->dir, refl.dir));
	refl.indice = ray->indice;
	refl.orig = ray->hit_point;
	refl = intersect_obj(refl, FALSE, FALSE);
	if (iter_refl > 0 && refl.solut != -1)
	{
		return (color_add(c, color_mult(compute_light(refl, --iter_refl,
		iter_trans), (ray->obj_hit)->mater.int_refl)));
	}
	return (c);
}

t_color		compute_light_bis(t_data ray, int iter_refl, int iter_trans,
	t_color c)
{
	if (ray.obj_hit->mater.int_trans > 0)
		c = color_stack(c, transparent_lighting(&ray, iter_refl, iter_trans,
			color_new(0, 0, 0)));
	if (ray.obj_hit->mater.int_refl > 0)
		c = color_stack(c, reflection_lighting(&ray, iter_refl, iter_trans,
			color_new(0, 0, 0)));
	c = color_mult(c, 1 / (float)ray.lights);
	return (color_add(c, color_mult(get_texture(ray,
	ray.obj_hit->mater.tex), g_env.scene.ambiant)));
}

void		compute_light2(float *coef, t_color *c, t_data *ray, t_light *l)
{
	*coef = get_shadow(l, ray);
	*c = color_stack(*c, color_mult(diffuse_lighting(ray, l), *coef));
	if (*coef >= 0.9 && ray->obj_hit->mater.shiny != 0)
		*c = color_stack(*c, color_mult(specular_lighting(ray, l), *coef));
	ray->lights++;
}

t_color		compute_light(t_data ray, int iter_refl, int iter_trans)
{
	t_color		c;
	t_light		*l;
	float		coef;

	l = g_env.scene.lgt;
	c = color_new(0, 0, 0);
	ray.lights = 0;
	ray.hit_point = vec_add(ray.orig, vec_mult(ray.dir, ray.solut));
	get_norm(&ray);
	if (ray.obj_hit->type == OCULUS)
		return (transparent_lighting(&ray, iter_refl, ++iter_trans, c));
	if (ray.obj_hit->type == SKYBOX)
		return (get_texture(ray, ray.obj_hit->mater.tex));
	while (l)
	{
		if (l->intensity > 0)
			compute_light2(&coef, &c, &ray, l);
		l = l->next;
	}
	return (compute_light_bis(ray, iter_refl, iter_trans, c));
}

t_color		render_ray(t_data ray)
{
	t_color color;

	if (ray.solut != -1 && ray.obj_hit)
	{
		if (ray.obj_hit->type == OCULUS)
			color = compute_light(ray, g_env.scene.iter_refl,
			g_env.scene.iter_trans + 2);
		else
			color = compute_light(ray, g_env.scene.iter_refl,
			g_env.scene.iter_trans);
	}
	else
		color = color_new(0, 0, 0);
	return (color);
}
