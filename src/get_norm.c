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

void	norm_cylinder(t_data *ray)
{
	float	t;
	t_vect	dir;
	t_vect	pos;

	dir = (ray->obj_hit)->dir;
	pos = (ray->obj_hit)->pos;
	t = (-dir.x * pos.x - dir.y * pos.y - dir.z * pos.z + ray->hit_point.x *
	dir.x + ray->hit_point.y * dir.y + ray->hit_point.z * dir.z) / (SQ(dir.x) +
	SQ(dir.y) + SQ(dir.z));
	ray->norm = vec_new(ray->hit_point.x - (pos.x + dir.x * t), ray->hit_point.y
	- (pos.y + dir.y * t), ray->hit_point.z - (pos.z + dir.z * t));
	ray->norm = vec_norm(ray->norm);
}

void	get_norm(t_data *ray)
{
	if ((ray->obj_hit)->type == SPHERE)
		ray->norm = vec_norm(vec_sub(ray->hit_point, (ray->obj_hit)->pos));
	if ((ray->obj_hit)->type == PLANE)
		ray->norm = (ray->obj_hit)->norm;
	if ((ray->obj_hit)->type == CYLINDER)
		norm_cylinder(ray);
}
