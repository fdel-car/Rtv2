/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 13:55:38 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/09 15:12:44 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	sphere_cut(float *r, t_data ray, t_vect cut_pos, t_vect cut)
{
	t_vect	u;
	t_vect	hit;

	if (vec_is_null(cut))
	{
		if (r[0] > EPSILON)
			return (r[0]);
		if (r[1] > EPSILON)
			return (r[1]);
		return (-1);
	}
	hit = vec_add(ray.orig, vec_mult(ray.dir, r[0]));
	u = vec_sub(hit, cut_pos);
	if (vec_dotp(cut, u) < 0 || r[0] < EPSILON)
	{
		hit = vec_add(ray.orig, vec_mult(ray.dir, r[1]));
		u = vec_sub(hit, cut_pos);
		if (vec_dotp(cut, u) > 0 && r[1] > EPSILON)
			return (r[1]);
		return (-1);
	}
	return (r[0]);
}

float	cut_basics(t_data *ray, t_obj *o, t_vect cut, float *r)
{
	float		m;

	m = vec_dotp(ray->dir, cut) * r[0] + vec_dotp(ray->orig, cut);
	if (m > o->max || m < o->min || r[0] < EPSILON)
	{
		m = vec_dotp(ray->dir, cut) * r[1] + vec_dotp(ray->orig, cut);
		if (m < o->max && m > o->min && r[1] > EPSILON)
			return (r[1]);
		return (-1);
	}
	return (r[0]);
}

float	quadratic_root(float a, float b, float c, float *roots)
{
	float	delta;
	float	solut;

	delta = SQ(b) - 4.0 * a * c;
	roots[0] = -1;
	roots[1] = -1;
	if (delta >= 0.0)
	{
		delta = sqrt(delta);
		roots[0] = (-b + delta) / (2.0 * a);
		roots[1] = (-b - delta) / (2.0 * a);
		solut = roots[0];
		roots[0] = roots[0] < roots[1] ? roots[0] : roots[1];
		roots[1] = solut < roots[1] ? roots[1] : solut;
		solut = roots[0] > EPSILON ? roots[0] : roots[1];
		if (solut > EPSILON)
			return (solut);
	}
	return (-1);
}
