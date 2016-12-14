/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 16:02:16 by vde-la-s          #+#    #+#             */
/*   Updated: 2016/12/14 14:40:35 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	run_sampling(float **rs,
int *nsh, t_data **vals, t_light *l)
{
	while (rs[0][0] < rs[1][1])
	{
		rs[0][1] = 0;
		while (rs[0][1] < rs[1][1])
		{
			rs[0][2] = 0;
			while (rs[0][2] < rs[1][1])
			{
				vals[0]->dir = vec_norm(vec_add(vec_sub(vals[1]->hit_point,
				l->pos), vec_new(rs[0][0], rs[0][1], rs[0][2])));
				if ((*(vals[0]) = intersect_obj(*vals[0],
				TRUE, FALSE)).solut != -1 &&
				vals[0]->obj_hit != vals[1]->obj_hit)
					++(*nsh);
				rs[0][2] += rs[1][0];
			}
			rs[0][1] += rs[1][0];
		}
		rs[0][0] += rs[1][0];
	}
}

float	get_msoft_shadow(t_light *l, t_data *ray)
{
	float	r[3];
	t_data	sh;
	int		nsh;
	float	sample[2];

	sample[0] = 0.1;
	sample[1] = 0.3;
	nsh = 0;
	sh.orig = l->pos;
	r[0] = 0;
	if (!l || !ray)
		return (1.0);
	run_sampling((float*[2]){r, sample}, &nsh, (t_data*[2]){&sh, ray}, l);
	return (1.0 - ((float)nsh /
	powf(sample[1] / sample[0], 3.0)));
}

float	get_dir_shadow(t_light *l, t_data *sh, t_data *ray, float coef)
{
	sh->orig = ray->hit_point;
	sh->dir = vec_mult(l->dir, -1);
	*sh = intersect_obj(*sh, TRUE, FALSE);
	if (sh->solut == -1)
		return (1.0);
	if (sh->obj_hit == ray->obj_hit)
		return (1.0);
	coef = sh->obj_hit && 1.0 - sh->obj_hit->mater.int_trans > 0 ?
	sh->obj_hit->mater.int_trans : 1.0;
	return (0.3 * coef);
}

float	get_shadow(t_light *l, t_data *ray)
{
	t_data	sh;
	t_vect	tmp;
	float	coef;

	coef = 1.0;
	if (l->type != DIR_L &&
	g_env.scene.soft_shadow > 0)
		return (get_msoft_shadow(l, ray));
	if (l->type == DIR_L)
		return (get_dir_shadow(l, &sh, ray, coef));
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
