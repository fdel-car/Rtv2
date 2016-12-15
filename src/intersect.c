/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/21 14:33:06 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/15 12:31:49 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	intersect_triangle(t_obj *obj, t_data ray)
{
	float		fl[4];
	t_vect		vc[3];

	vc[0] = cross_pr(ray.dir, obj->v);
	fl[0] = vec_dotp(obj->u, vc[0]);
	if (fl[0] < 0.00001 && fl[0] > -0.00001)
		return (-1);
	vc[1] = vec_sub(ray.orig, obj->v0);
	fl[1] = vec_dotp(vc[1], vc[0]) * (1 / fl[0]);
	if (fl[1] < 0 || fl[1] > 1)
		return (-1);
	vc[2] = cross_pr(vc[1], obj->u);
	fl[2] = vec_dotp(ray.dir, vc[2]) * (1 / fl[0]);
	if (fl[2] < 0 || (fl[1] + fl[2]) > 1)
		return (-1);
	fl[3] = vec_dotp(obj->v, vc[2]) * (1 / fl[0]);
	if (fl[3] > 0.00001)
		return (fl[3]);
	return (-1);
}

float	intersect_sphere(t_obj *obj, t_data ray)
{
	float	a;
	float	b;
	float	c;
	float	r[2];

	if (!ft_strcmp("sphere_oculus", obj->name) && !g_env.oculus)
		return (-1);
	a = SQ(ray.dir.x) + SQ(ray.dir.y) + SQ(ray.dir.z);
	b = 2.0 * (ray.dir.x * (ray.orig.x - obj->pos.x) + ray.dir.y *
	(ray.orig.y - obj->pos.y) + ray.dir.z * (ray.orig.z - obj->pos.z));
	c = (SQ(ray.orig.x - obj->pos.x) + SQ(ray.orig.y - obj->pos.y) +
	SQ(ray.orig.z - obj->pos.z)) - SQ(obj->rayon);
	quadratic_root(a, b, c, r);
	return (texture_cutr(sphere_cut(r, ray, obj->cut_pos, obj->cut),
	r, obj, ray));
}

float	intersect_plane(t_obj *obj, t_data ray)
{
	float	solut;
	t_vect	hit;

	solut = -vec_dotp(vec_sub(ray.orig, obj->pos), obj->norm) /
		vec_dotp(obj->norm, ray.dir);
	if (solut > EPSILON)
	{
		hit = vec_add(ray.orig, vec_mult(ray.dir, solut));
		if (SQ(hit.x - obj->pos.x) + SQ(hit.y - obj->pos.y) + SQ(hit.z -
		obj->pos.z) > SQ(obj->sphere_cut) && obj->sphere_cut != 0)
			return (-1);
		return (texture_cut(solut, obj, ray));
	}
	return (-1);
}

float	intersect_cone(t_obj *obj, t_data ray)
{
	float	a;
	float	b;
	float	c;
	t_vect	tmp;
	float	r[2];

	tmp = vec_sub(ray.orig, obj->pos);
	a = vec_dotp(ray.dir, ray.dir) - ((1.0 + SQ(obj->alpha)) *
	SQ(vec_dotp(ray.dir, obj->dir)));
	b = 2.0 * (vec_dotp(ray.dir, tmp) - ((1.0 + SQ(obj->alpha))
	* vec_dotp(ray.dir, obj->dir) * vec_dotp(tmp, obj->dir)));
	c = vec_dotp(tmp, tmp) - ((1.0 + SQ(obj->alpha)) *
	SQ(vec_dotp(tmp, obj->dir)));
	if (obj->min == 0 && obj->max == 0)
		return (texture_cutr(quadratic_root(a, b, c, r), r, obj, ray));
	if (!quadratic_root(a, b, c, r))
		return (-1);
	return (texture_cutr(cut_basics(&ray, obj, vec_is_null(obj->cut)
	? obj->dir : obj->cut, r), r, obj, ray));
}

float	intersect_cylinder(t_obj *obj, t_data ray)
{
	float	a;
	float	b;
	float	c;
	t_vect	tmp;
	float	r[2];

	tmp = vec_sub(ray.orig, obj->pos);
	a = vec_dotp(ray.dir, ray.dir) - (SQ(vec_dotp(ray.dir, obj->dir)));
	b = 2.0 * (vec_dotp(ray.dir, tmp) - (vec_dotp(ray.dir,
	obj->dir) * vec_dotp(tmp, obj->dir)));
	c = vec_dotp(tmp, tmp) - (SQ(vec_dotp(tmp, obj->dir))) - SQ(obj->rayon);
	if (obj->min == 0 && obj->max == 0)
		return (texture_cutr(quadratic_root(a, b, c, r), r, obj, ray));
	if (!quadratic_root(a, b, c, r))
		return (-1);
	return (texture_cutr(cut_basics(&ray, obj, vec_is_null(obj->cut)
	? obj->dir : obj->cut, r), r, obj, ray));
}
