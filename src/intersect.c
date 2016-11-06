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
	t_vect		vc[5];

	vc[0] = vec_sub(obj->v1, obj->v0);
	vc[1] = vec_sub(obj->v2, obj->v0);
	vc[2] = cross_pr(ray.dir, vc[1]);
	fl[0] = vec_dotp(vc[0], vc[2]);
	if (fl[0] < EPSILON && fl[0] > -EPSILON)
		return (-1);
	vc[3] = vec_sub(ray.orig, obj->v0);
	fl[1] = vec_dotp(vc[3], vc[2]) * (1 / fl[0]);
	if (fl[1] < 0 || fl[1] > 1)
		return (-1);
	vc[4] = cross_pr(vc[3], vc[0]);
	fl[2] = vec_dotp(ray.dir, vc[4]) * (1 / fl[0]);
	if (fl[2] < 0 || (fl[1] + fl[2]) > 1)
		return (-1);
	fl[3] = vec_dotp(vc[1], vc[4]) * (1 / fl[0]);
	if (fl[3] > EPSILON)
		return (fl[3]);
	return (-1);
}

float	intersect_sphere(t_obj *obj, t_data ray)
{
	float a, b, c, delta, t1, t2, solut;

	a = SQ(ray.dir.x) + SQ(ray.dir.y) + SQ(ray.dir.z);
	b = 2.0 * (ray.dir.x * (ray.orig.x - obj->pos.x) + ray.dir.y *
			(ray.orig.y - obj->pos.y) + ray.dir.z * (ray.orig.z - obj->pos.z));
	c = (SQ(ray.orig.x - obj->pos.x) + SQ(ray.orig.y - obj->pos.y) +
			SQ(ray.orig.z - obj->pos.z)) - SQ(obj->rayon);
	delta = (b * b) - 4.0 * a * c;
	if (delta >= 0)
	{
		delta = sqrt(delta);
		t1 = (-b + delta) / (2.0 * a);
		t2 = (-b - delta) / (2.0 * a);
		solut = t1 > t2 ? t2 : t1;
		if (solut > EPSILON)
			return (solut);
	}
	return (-1);
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
	float	a, b, c, delta, t1, t2, solut;
	t_vect	tmp;

	tmp = vec_sub(ray.orig, obj->pos);
	a = vec_dotp(ray.dir, ray.dir) - ((1.0 + SQ(obj->alpha)) *
			SQ(vec_dotp(ray.dir, obj->dir)));
	b = 2.0 * (vec_dotp(ray.dir, tmp) - ((1.0 + SQ(obj->alpha))
				* vec_dotp(ray.dir, obj->dir) * vec_dotp(tmp, obj->dir)));
	c = vec_dotp(tmp, tmp) - ((1.0 + SQ(obj->alpha)) *
			SQ(vec_dotp(tmp, obj->dir)));
	delta = SQ(b) - 4.0 * a * c;
	if (delta >= 0.0)
	{
		delta = sqrt(delta);
		t1 = (-b + delta) / (2.0 * a);
		t2 = (-b - delta) / (2.0 * a);
		solut = t1 < t2 && t1 > EPSILON ? t1 : t2;
		if (solut > EPSILON)
			return (solut);
	}
	return (-1);
}

float	intersect_cylinder(t_obj *obj, t_data ray)
{
	float	a, b, c, delta, t1, t2, solut;
	t_vect	tmp;

	tmp = vec_sub(ray.orig, obj->pos);
	a = vec_dotp(ray.dir, ray.dir) - (SQ(vec_dotp(ray.dir, obj->dir)));
	b = 2.0 * (vec_dotp(ray.dir, tmp) - (vec_dotp(ray.dir,
					obj->dir) * vec_dotp(tmp, obj->dir)));
	c = vec_dotp(tmp, tmp) - (SQ(vec_dotp(tmp, obj->dir))) - SQ(obj->rayon);
	delta = SQ(b) - 4.0 * a * c;
	if (delta >= 0.0)
	{
		delta = sqrt(delta);
		t1 = (-b + delta) / (2.0 * a);
		t2 = (-b - delta) / (2.0 * a);
		solut = t1 < t2 ? t1 : t2;
		if (solut > EPSILON)
			return (solut);
	}
	return (-1);
}
