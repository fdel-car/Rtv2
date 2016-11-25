/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.ray2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 16:47:22 by fdel-car          #+#    #+#             */
/*   Updated: 2016/11/25 18:22:59 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color		diffuse_lighting(t_data *ray, t_light *l)
{
	t_color	c;
	float	cos;
	float	ang;

	c = color_new(0, 0, 0);
	if (l->type == POINT_L || l->type == SPOT_L)
		ray->light = vec_norm(vec_sub(l->pos, ray->hit_point));
	if (l->type == DIR_L)
		ray->light = vec_mult(l->dir, -1);
	if (l->type == SPOT_L)
	{
		ang = vec_dotp(l->dir, vec_mult(ray->light, -1));
		if (acos(ang) > l->alpha)
			return (c);
	}
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

t_vect		refract_dir(t_data *ray, t_obj *obj)
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
	{
		return (color_add(c, color_mult(compute_light(refr, iter_refl),
		(ray->obj_hit)->mater.int_trans)));
	}
	return (c);
}
