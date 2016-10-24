/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/21 14:33:06 by fdel-car          #+#    #+#             */
/*   Updated: 2016/08/21 14:33:10 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
		if (solut > 0.0)
			return (solut);
	}
	return (-1);
}

float	intersect_plane(t_obj *obj, t_data ray)
{
	float solut;

	solut = -dotp_vec_norm(vec_sub(ray.orig, obj->pos), obj->norm) /
	dotp_vec_norm(obj->norm, ray.dir);
	if (solut > 0)
		return (solut);
	return (-1);
}
