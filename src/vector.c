/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 16:26:43 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/15 13:45:13 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vect	vec_mult(t_vect u, float value)
{
	t_vect w;

	w.x = u.x * value;
	w.y = u.y * value;
	w.z = u.z * value;
	return (w);
}

t_vect	vec_mul(t_vect u, t_vect v)
{
	t_vect w;

	w.x = u.x * v.x;
	w.y = u.y * v.y;
	w.z = u.z * v.z;
	return (w);
}

t_vect	vec_sub(t_vect u, t_vect v)
{
	t_vect w;

	w.x = u.x - v.x;
	w.y = u.y - v.y;
	w.z = u.z - v.z;
	return (w);
}

t_vect	vec_add(t_vect u, t_vect v)
{
	t_vect w;

	w.x = u.x + v.x;
	w.y = u.y + v.y;
	w.z = u.z + v.z;
	return (w);
}

t_vect	vec_norm(t_vect u)
{
	t_vect	w;
	float	length;

	if (vec_is_null(u))
		return (u);
	length = sqrt((u.x * u.x) + (u.y * u.y) + (u.z * u.z));
	w.x = u.x / length;
	w.y = u.y / length;
	w.z = u.z / length;
	return (w);
}
