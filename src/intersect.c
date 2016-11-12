/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/21 14:33:06 by fdel-car          #+#    #+#             */
/*   Updated: 2016/11/06 19:53:19 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	intersect_triangle(t_obj *obj, t_data ray)
{
	float       fl[4];
	t_vect		vc[3];

	vc[0] = cross_pr(ray.dir, obj->v);
	fl[0] = vec_dotp(obj->u, vc[0]);
	if (fl[0] < 0.001 && fl[0] > -0.001)
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
	if (fl[3] > 0.001)
		return (fl[3]);
	return (-1);
}

float	intersect_sphere(t_obj *obj, t_data ray)
{
	float	a;
	float	b;
	float	c;

	a = SQ(ray.dir.x) + SQ(ray.dir.y) + SQ(ray.dir.z);
	b = 2.0 * (ray.dir.x * (ray.orig.x - obj->pos.x) + ray.dir.y *
	(ray.orig.y - obj->pos.y) + ray.dir.z * (ray.orig.z - obj->pos.z));
	c = (SQ(ray.orig.x - obj->pos.x) + SQ(ray.orig.y - obj->pos.y) +
	SQ(ray.orig.z - obj->pos.z)) - SQ(obj->rayon);
	return (quadratic_root(a, b, c));
}

float	intersect_plane(t_obj *obj, t_data ray)
{
	float solut;

	solut = -vec_dotp(vec_sub(ray.orig, obj->pos), obj->norm) /
		vec_dotp(obj->norm, ray.dir);
	if (solut > EPSILON)
		return (solut);
	return (-1);
}

float	intersect_cone(t_obj *obj, t_data ray)
{
	float	a;
	float	b;
	float	c;
	t_vect	tmp;

	tmp = vec_sub(ray.orig, obj->pos);
	a = vec_dotp(ray.dir, ray.dir) - ((1.0 + SQ(obj->alpha)) *
	SQ(vec_dotp(ray.dir, obj->dir)));
	b = 2.0 * (vec_dotp(ray.dir, tmp) - ((1.0 + SQ(obj->alpha))
	* vec_dotp(ray.dir, obj->dir) * vec_dotp(tmp, obj->dir)));
	c = vec_dotp(tmp, tmp) - ((1.0 + SQ(obj->alpha)) *
	SQ(vec_dotp(tmp, obj->dir)));
	return (quadratic_root(a, b, c));
}

float	intersect_cylinder(t_obj *obj, t_data ray)
{
	float	a;
	float	b;
	float	c;
	t_vect	tmp;

	tmp = vec_sub(ray.orig, obj->pos);
	a = vec_dotp(ray.dir, ray.dir) - (SQ(vec_dotp(ray.dir, obj->dir)));
	b = 2.0 * (vec_dotp(ray.dir, tmp) - (vec_dotp(ray.dir,
	obj->dir) * vec_dotp(tmp, obj->dir)));
	c = vec_dotp(tmp, tmp) - (SQ(vec_dotp(tmp, obj->dir))) - SQ(obj->rayon);
	return (quadratic_root(a, b, c));
}

float	intersect_torus(t_obj *obj, t_data ray)
{
	float	m, n, o, p, q;
	float	a, b, c, d, e;
	t_vect	tmp;

	tmp = vec_sub(ray.orig, obj->pos);
	m = vec_dotp(ray.dir, ray.dir);
	n = vec_dotp(ray.dir, tmp);
	o = vec_dotp(tmp, tmp);
	p = vec_dotp(ray.dir, obj->dir);
	q = vec_dotp(tmp, obj->dir);
	a = SQ(m);
	b = 4 * m * n;
	c = 4 * SQ(m) + 2 * m * o - 2 * (SQ(obj->rayon_large) + SQ(obj->rayon)) * m
	+ 4 * SQ(obj->rayon_large) * SQ(p);
	d = 4 * n * o - 4 * (SQ(obj->rayon_large) + SQ(obj->rayon)) * n + 8 *
	SQ(obj->rayon_large) * p * q;
	e = SQ(o) - 2 * (SQ(obj->rayon_large) + SQ(obj->rayon)) * o + 4 *
	SQ(obj->rayon_large) * SQ(q) + SQ((SQ(obj->rayon_large) - SQ(obj->rayon)));
	// return (quartic_root(a, b, c, d, e));
	return (-1);
}
