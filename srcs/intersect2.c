/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:34:42 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/09 17:14:43 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	texture_cutr(float res, float *r, t_obj *o, t_data mray)
{
	float	tmp;

	if (!o || !o->mater.ctex)
		return (res);
	if (res < 0 || !r)
		return (-1);
	tmp = texture_cut(res, o, mray);
	if (tmp > 0)
		return (tmp);
	tmp = texture_cut(r[1], o, mray);
	if (tmp > 0)
		return (tmp);
	return (-1);
}

float	texture_cut(float res, t_obj *o, t_data mray)
{
	t_color	p;

	if (!o || !o->mater.ctex)
		return (res);
	if (res < 0)
		return (-1);
	mray.obj_hit = o;
	mray.hit_point = vec_add(mray.orig, vec_mult(mray.dir, res));
	get_norm(&mray);
	p = get_texture(mray, o->mater.ctex);
	if (p.r == 255 && p.g == 255 && p.b == 255)
		return (res);
	return (-1);
}
