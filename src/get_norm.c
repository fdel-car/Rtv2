/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_norm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 15:35:21 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/08 15:05:19 by fdel-car         ###   ########.fr       */
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

void	norm_cone(t_data *ray)
{
	float	t;
	float	beta;
	t_vect	dir;

	dir = (ray->obj_hit)->dir;
	beta = vec_dotp(vec_norm(vec_sub(ray->hit_point,
	(ray->obj_hit)->pos)), dir);
	if ((acos(beta) * 180.0 / M_PI) > 90.0)
	{
		dir = vec_mult(dir, -1);
		beta = vec_dotp(vec_norm(vec_sub(ray->hit_point, (ray->obj_hit)->pos)),
		dir);
	}
	t = (dist_p((ray->obj_hit)->pos, ray->hit_point) * sin(beta)) / sin(1.5708 +
	beta);
	dir = vec_mult(dir, t);
	dir = vec_add((ray->obj_hit)->pos, dir);
	ray->norm = vec_norm(vec_sub(ray->hit_point, dir));
}

void	normal_mapping(t_data *ray)
{
	t_color		p;

	p = color_new(0, 0, 0);
	if (ray->obj_hit->type == SPHERE)
		p = getex_sphere(*ray, ray->obj_hit->mater.ntex);
	else if (ray->obj_hit->type == PLANE)
		p = getex_plane(*ray, ray->obj_hit->mater.ntex);
	else if (ray->obj_hit->type == CYLINDER ||
	ray->obj_hit->type == CONE)
		p = getex_cyl(*ray, ray->obj_hit->mater.ntex);
	ray->norm = vec_norm(vec_add(ray->norm, bump_normal(p)));
}

void	get_norm(t_data *ray)
{
	if ((ray->obj_hit)->type == SPHERE || (ray->obj_hit)->type == OCULUS)
		ray->norm = vec_norm(vec_sub(ray->hit_point, (ray->obj_hit)->pos));
	if ((ray->obj_hit)->type == PLANE ||
		(ray->obj_hit)->type == TRIANGLE)
		ray->norm = (ray->obj_hit)->norm;
	if ((ray->obj_hit)->type == CYLINDER)
		norm_cylinder(ray);
	if ((ray->obj_hit)->type == CONE)
		norm_cone(ray);
	if ((ray->obj_hit)->mater.ntex)
		normal_mapping(ray);
}
