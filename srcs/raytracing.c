/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 17:53:11 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/13 15:32:48 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_data		intersect_obj(t_data ray, gboolean sh, gboolean prev)
{
	t_obj	*obj;

	ray.solut = -1;
	ray.obj_hit = NULL;
	obj = g_env.scene.obj;
	if (sh == TRUE || prev == TRUE)
		obj = obj->next;
	loop_intersect(&ray, sh, obj);
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
	g_env.scene.cam.x_ind_p = g_env.scene.cam.view_w / (float)WIDTH_PREVIEW;
	g_env.scene.cam.y_ind_p = g_env.scene.cam.view_h / (float)HEIGHT_PREVIEW;
	g_env.scene.cam.pos1 = g_env.scene.cam.pos;
	g_env.scene.cam.c_pos = 1;
}

t_color		init_ray(float x, float y, t_data ray)
{
	t_vect	view_point;

	view_point = vec_sub(vec_add(g_env.scene.cam.up_left,
	vec_mult(g_env.scene.cam.right,
	g_env.scene.cam.x_ind * x)), vec_mult(g_env.scene.cam.up,
	g_env.scene.cam.y_ind * y));
	ray.dir = vec_norm(vec_sub(view_point, g_env.scene.cam.pos));
	if (g_env.oculus == TRUE)
		return (render_ray(oculus_view(ray)));
	return (render_ray(intersect_obj(ray, FALSE, FALSE)));
}

void		super_sample(float x, float y, t_data ray)
{
	float	ax;
	float	ay;
	float	aa_ind;
	t_color	c;

	ax = x;
	ay = y;
	aa_ind = 1.0 / g_env.scene.anti_alia;
	c = color_new(0, 0, 0);
	while (ax < x + 1.0)
	{
		while (ay < y + 1.0)
		{
			c = color_stack(c, init_ray(ax, ay, ray));
			ay += aa_ind;
		}
		ax += aa_ind;
	}
	c = color_mult(c, (1.0 / (float)g_env.scene.anti_alia));
	put_pixel(x, y, c);
}

void		*raytracing(void *arg)
{
	int		*tmp;
	int		x;
	int		x_max;
	int		y;
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
			if (g_env.scene.anti_alia > 1)
				super_sample(x, y, ray);
			else
				put_pixel(x, y, init_ray(x, y, ray));
			display_progress_bar();
			y++;
		}
		x++;
	}
	pthread_exit(NULL);
}
