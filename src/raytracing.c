/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 17:53:11 by fdel-car          #+#    #+#             */
/*   Updated: 2016/10/24 17:53:13 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_data	intersect_obj(t_data ray)
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

void	init_view(void)
{
	g_env.scene.cam.up = vec_new(0, 1, 0);
	g_env.scene.cam.view_d = 1.5;
	g_env.scene.cam.view_h = 1.4;
	g_env.scene.cam.view_w = 2.4;
	g_env.scene.cam.x_ind = g_env.scene.cam.view_w / (float)WIDTH;
	g_env.scene.cam.y_ind = g_env.scene.cam.view_h / (float)HEIGHT;
}

t_color	compute_light(t_data ray)
{
	t_color c;
	t_color cl;
	t_light	*l;
	t_vect	light;
	float	cos;

	// return ((ray.obj_hit)->mater.color);
	c = color_new(0, 0, 0);
	ray.hit_point = vec_add(ray.orig, vec_mult(ray.dir, ray.solut));
	l = g_env.scene.lgt;
	ray.norm = get_norm(ray);
	light = vec_norm(vec_sub(l->pos, ray.hit_point));
	cos = dotp_vec_norm(light, ray.norm);
	cl = color_mult(l->color, l->intensity);
	if (cos > 0)
		c = color_mult((ray.obj_hit)->mater.color, cos);
	c = color_add(c, color_mult((ray.obj_hit)->mater.color, 0.2));
	// c = color_mult(color_add(c, cl), 0.5);
	return (c);
}

void	render_ray(t_data ray, int x, int y)
{
	t_color color;

	if (ray.solut != -1 && ray.obj_hit)
	{
		color = compute_light(ray);
		put_pixel(x, y, color);
	}
	else
		put_pixel(x, y, color_new(0, 0, 0));
}

void	*raytracing(void *arg)
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
