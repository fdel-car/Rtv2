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

void	get_norm(t_data *ray)
{
	if ((ray->obj_hit)->type == SPHERE)
		ray->norm = vec_norm(vec_sub(ray->hit_point, (ray->obj_hit)->pos));
	if ((ray->obj_hit)->type == PLANE)
		ray->norm = (ray->obj_hit)->norm;
}
