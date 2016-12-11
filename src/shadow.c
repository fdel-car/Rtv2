/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 16:02:16 by vde-la-s          #+#    #+#             */
/*   Updated: 2016/12/11 17:28:44 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	get_msoft_shadow(t_light *l, t_data *ray)
{
	float	r[3];
	t_data	sh;
	int		nsh;
	float	sample[2];

	sample[0] = 0.2;
	sample[1] = 0.4;
	nsh = 0;
	sh.orig = l->pos;
	r[0] = 0;
	while (r[0] < sample[1])
	{
		r[1] = 0;
		while (r[1] < sample[1])
		{
			r[2] = 0;
			while (r[2] < sample[1])
			{
				sh.dir = vec_norm(vec_add(vec_sub(ray->hit_point,
				l->pos), vec_new(r[0], r[1], r[2])));
				if ((sh = intersect_obj(sh, TRUE, FALSE)).solut != -1 &&
				sh.obj_hit != ray->obj_hit)
					++nsh;
				r[2] += sample[0];
			}
			r[1] += sample[0];
		}
		r[0] += sample[0];
	}
	return (1.0 - ((float)nsh /
	powf(sample[1] / sample[0], 3.0)));
}

float	get_shadow(t_light *l, t_data *ray)
{
	t_data	sh;
	t_vect	tmp;
	float	coef;

	if (g_env.scene.soft_shadow > 0)
		return (get_msoft_shadow(l, ray));
	if (l->type == DIR_L)
	{
		sh.orig = ray->hit_point;
		sh.dir = vec_mult(l->dir, -1);
		sh = intersect_obj(sh, TRUE, FALSE);
		if (sh.solut == -1)
			return (1.0);
		if (sh.obj_hit == ray->obj_hit)
			return (1.0);
		coef = sh.obj_hit && 1.0 - sh.obj_hit->mater.int_trans > 0 ?
		sh.obj_hit->mater.int_trans : 1.0;
		return (0.3 * coef);
	}
	sh.orig = l->pos;
	sh.dir = vec_norm(vec_sub(ray->hit_point, l->pos));
	sh = intersect_obj(sh, TRUE, FALSE);
	if (sh.obj_hit == ray->obj_hit)
		return (1.0);
	tmp = vec_add(sh.orig, vec_mult(sh.dir, sh.solut));
	coef = sh.obj_hit && 1.0 - sh.obj_hit->mater.int_trans > 0 ?
	sh.obj_hit->mater.int_trans : 1.0;
	if (dist_p(tmp, l->pos) < dist_p(ray->hit_point, l->pos) - EPSILON)
		return (0.3 * coef);
	return (1.0);
}
