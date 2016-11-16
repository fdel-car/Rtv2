/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preview.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 18:15:41 by fdel-car          #+#    #+#             */
/*   Updated: 2016/11/16 05:50:36 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	put_pixel_prev(int x, int y, t_color color)
{
	int pos;

	pos = y * g_env.rowstride_prev + x * 3;
	g_env.pixels_prev[pos] = color.r;
	g_env.pixels_prev[pos + 1] = color.g;
	g_env.pixels_prev[pos + 2] = color.b;
}

t_color		compute_light_prev(t_data ray)
{
	t_color		c;
	t_color		ambiant;
	t_light		*l;
	int			lights;

	lights = 0;
	l = g_env.scene.lgt;
	ambiant = color_mult(get_texture(ray), 0.2);
	c = color_new(0, 0, 0);
	ray.hit_point = vec_add(ray.orig, vec_mult(ray.dir, ray.solut));
	if (ft_strcmp(ray.obj_hit->name, "skybox") == 0)
		return (get_texture(ray));
	get_norm(&ray);
	while (l)
	{
		c = color_stack(c, diffuse_lighting(&ray, l));
		l = l->next;
		lights++;
	}
	c = color_mult(c, 1.0 / (float)lights);
	c = color_add(c, ambiant);
	return (c);
}


t_color		render_ray_prev(t_data ray)
{
	t_color color;

	if (ray.solut != -1 && ray.obj_hit)
		color = compute_light_prev(ray);
	else
		color = color_new(0, 0, 0);
	return (color);
}

t_color		init_ray_prev(float x, float y, t_data ray)
{
	t_vect	view_point;

	view_point = vec_sub(vec_add(g_env.scene.cam.up_left,
	vec_mult(g_env.scene.cam.right,
	g_env.scene.cam.x_ind_p * x)), vec_mult(g_env.scene.cam.up,
	g_env.scene.cam.y_ind_p * y));
	ray.dir = vec_norm(vec_sub(view_point, g_env.scene.cam.pos));
	return (render_ray_prev(intersect_obj(ray)));
}

void		*raytracing_prev(void *arg)
{
	int		*tmp;
	int		x, x_max, y;
	t_data	ray;

	tmp = (int *)arg;
	x = *tmp;
	x_max = x + WIDTH_PREVIEW / NUM_THREAD;
	ray.orig = g_env.scene.cam.pos;
	while (x < x_max)
	{
		y = 0;
		while (y < HEIGHT_PREVIEW)
		{
			put_pixel_prev(x, y, init_ray_prev(x, y, ray));
			y++;
		}
		x++;
	}
	pthread_exit(NULL);
}

void	launch_preview(void)
{
	g_env.scene.cam.right = cross_pr(g_env.scene.cam.up, g_env.scene.cam.dir);
	g_env.scene.cam.up = cross_pr(g_env.scene.cam.dir, g_env.scene.cam.right);
	g_env.scene.cam.up_left = vec_add(g_env.scene.cam.pos,
	vec_add(vec_mult(g_env.scene.cam.dir, g_env.scene.cam.view_d),
	vec_sub(vec_mult(g_env.scene.cam.up, (g_env.scene.cam.view_h / 2.0)),
	vec_mult(g_env.scene.cam.right, (g_env.scene.cam.view_w / 2.0)))));
	g_env.id_thread = 0;
	while (g_env.id_thread < NUM_THREAD)
	{
		pthread_create(&g_env.thread[g_env.id_thread], NULL, raytracing_prev,
		&g_env.limits_prev[g_env.id_thread]);
		g_env.id_thread++;
	}
	g_env.id_thread = 0;
	while (g_env.id_thread < NUM_THREAD)
	{
		pthread_join(g_env.thread[g_env.id_thread], NULL);
		g_env.id_thread++;
	}
	gtk_image_set_from_pixbuf(GTK_IMAGE(g_env.prev), g_env.pix_prev);
}
