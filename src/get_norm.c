/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_norm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 15:35:21 by fdel-car          #+#    #+#             */
/*   Updated: 2016/10/24 15:35:23 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vect		get_norm(t_data ray)
{
	t_vect n;

	n = vec_new(0, 0, 0);
	if (ray.obj_hit->type == SPHERE)
		n = vec_norm(vec_sub(ray.hit_point, ray.obj_hit->pos));
	if (ray.obj_hit->type == PLANE)
		n = ray.obj_hit->norm;//vec_sub(ray.obj_hit->dir, ray.obj_hit->dir);
	return (n);
}
