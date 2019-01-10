/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.ray2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 16:47:22 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/11 17:25:48 by fdel-car         ###   ########.fr       */
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
		, color_mult(get_texture(*ray, ray->obj_hit->mater.tex), l->intensity *
		cos));
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
	float	cos;

	cos = vec_dotp(ray->norm, ray->dir);
	if (cos > 0)
	{
		n1 = obj->mater.indice;
		n2 = 1.0;
		ray->norm = vec_mult(ray->norm, -1.0);
	}
	else
	{
		n1 = 1.0;
		n2 = obj->mater.indice;
		cos = -cos;
	}
	n = n1 / n2;
	return (refract_dir_bis(ray, obj, n, cos));
}

float		transparent_map(t_data *ray)
{
	t_color	p;
	float	r;

	r = (ray->obj_hit)->mater.int_trans;
	if ((ray->obj_hit)->mater.ttex)
	{
		p = get_texture(*ray, (ray->obj_hit)->mater.ttex);
		r = (((float)p.r + (float)p.g + (float)p.b) / 3.0) / 255.0;
	}
	return (r);
}

t_color		transparent_lighting(t_data *ray, int iter_refl, int iter_trans,
	t_color c)
{
	t_data	refr;
	float	t_coef;

	refr.dir = vec_norm(refract_dir(ray, ray->obj_hit));
	refr.orig = ray->hit_point;
	refr = intersect_obj(refr, FALSE, FALSE);
	t_coef = transparent_map(ray);
	if (iter_trans > 0 && refr.solut != -1)
	{
		return (color_add(c, color_mult(compute_light(refr,
			iter_refl, --iter_trans), t_coef)));
	}
	return (c);
}
