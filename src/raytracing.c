/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 17:53:11 by fdel-car          #+#    #+#             */
/*   Updated: 2016/10/27 14:11:57 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_data		intersect_obj(t_data ray)
{
	t_obj	*obj;
	float	tmp;

	ray.solut = -1;
	ray.obj_hit = NULL;
	obj = g_env.scene.obj;
	while (obj)
	{
		tmp = (*obj->func)(obj, ray);
		if ((tmp < ray.solut || ray.solut == -1) && tmp != -1)
		{
			ray.obj_hit = obj;
			ray.solut = tmp;
		}
		obj = obj->next;
	}
	return (ray);
}

void		init_view(void)
{
	g_env.scene.cam.up = vec_new(0, 1, 0);
	g_env.scene.cam.view_d = 1.5;
	g_env.scene.cam.view_h = 1.4;
	g_env.scene.cam.view_w = 2.4;
	g_env.scene.cam.x_ind = g_env.scene.cam.view_w / (float)WIDTH;
	g_env.scene.cam.y_ind = g_env.scene.cam.view_h / (float)HEIGHT;
}

void		*raytracing(void *arg)
{
	int		*tmp;
	int		x, x_max, y;
	t_vect	view_point;
	t_data	ray;

	tmp = (int *)arg;
	x = *tmp;
	x_max = x + WIDTH / NUM_THREAD;
	ray.orig = g_env.scene.cam.pos;
	while (x < x_max)
	{
		y = 0;
		while (y < HEIGHT)
		{
			view_point = vec_sub(vec_add(g_env.scene.cam.up_left,
			vec_mult(g_env.scene.cam.right,
			g_env.scene.cam.x_ind * x)), vec_mult(g_env.scene.cam.up,
			g_env.scene.cam.y_ind * y));
			ray.dir = vec_norm(vec_sub(view_point, g_env.scene.cam.pos));
			render_ray(intersect_obj(ray), x, y);
			y++;
		}
		x++;
	}
	pthread_exit(NULL);
}
