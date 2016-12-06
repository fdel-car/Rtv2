/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/20 14:35:40 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/06 15:39:04 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	put_pixel(int x, int y, t_color color)
{
	int pos;

	pos = y * g_env.rowstride + x * 3;
	g_env.pixels[pos] = color.r;
	g_env.pixels[pos + 1] = color.g;
	g_env.pixels[pos + 2] = color.b;
}

void	pre_compute_tri(t_obj *o)
{
	t_obj *tmp;

	while (o)
	{
		if (o->type == TRIANGLE)
		{
			o->u = vec_sub(o->v1, o->v0);
			o->v = vec_sub(o->v2, o->v0);
		}
		if (o->type == MESH)
		{
			tmp = o->lst;
			while (tmp)
			{
				if (tmp->type == TRIANGLE)
				{
					tmp->u = vec_sub(tmp->v1, tmp->v0);
					tmp->v = vec_sub(tmp->v2, tmp->v0);
				}
				tmp = tmp->next;
			}
		}
		o = o->next;
	}
}

void 	stereo_func()
{
	if (g_env.stereo_red == TRUE)
	{
		red_filter();
		g_env.stereo_red = FALSE;
		g_env.scene.cam.pos = vec_add(g_env.scene.cam.pos,
		vec_mult(g_env.scene.cam.right, DIST_INTEROCULAR));
		g_env.scene.cam.dir = vec_norm(vec_sub(g_env.scene.cam.look_at,
		g_env.scene.cam.pos));
		launch_thread();
	}
	else
	{
		g_env.scene.cam.pos = vec_sub(g_env.scene.cam.pos,
		vec_mult(g_env.scene.cam.right, DIST_INTEROCULAR / 2));
		g_env.scene.cam.dir = vec_norm(vec_sub(g_env.scene.cam.look_at,
		g_env.scene.cam.pos));
		green_blue_filter();
		g_env.stereo_red = TRUE;
		gtk_image_set_from_pixbuf(GTK_IMAGE(g_env.img), g_env.filter);
	}
}

void	launch_thread(void)
{
	desactivate_preview();
	if (g_env.stereo == TRUE && g_env.stereo_red == TRUE)
	{
		g_env.scene.cam.pos = vec_sub(g_env.scene.cam.pos,
		vec_mult(g_env.scene.cam.right, DIST_INTEROCULAR / 2));
		g_env.scene.cam.dir = vec_norm(vec_sub(g_env.scene.cam.look_at,
		g_env.scene.cam.pos));
	}
	g_env.pixels_progress = 0;
	g_env.progress = 0;
	g_env.scene.cam.right = cross_pr(g_env.scene.cam.up, g_env.scene.cam.dir);
	g_env.scene.cam.up = cross_pr(g_env.scene.cam.dir, g_env.scene.cam.right);
	g_env.scene.cam.up_left = vec_add(g_env.scene.cam.pos,
	vec_add(vec_mult(g_env.scene.cam.dir, g_env.scene.cam.view_d),
	vec_sub(vec_mult(g_env.scene.cam.up, (g_env.scene.cam.view_h / 2.0)),
	vec_mult(g_env.scene.cam.right, (g_env.scene.cam.view_w / 2.0)))));
	pre_compute_tri(g_env.scene.obj);
	g_env.id_thread = 0;
	while (g_env.id_thread < NUM_THREAD)
	{
		pthread_create(&g_env.thread[g_env.id_thread], NULL, raytracing,
				&g_env.limits[g_env.id_thread]);
		g_env.id_thread++;
	}
	g_env.id_thread = 0;
	while (g_env.id_thread < NUM_THREAD)
	{
		pthread_join(g_env.thread[g_env.id_thread], NULL);
		g_env.id_thread++;
	}
	if (g_env.stereo == TRUE)
		stereo_func();
	else
		gtk_image_set_from_pixbuf(GTK_IMAGE(g_env.img), g_env.pix);
	check_filter();
}

void	init_limits(void)
{
	int iter;
	int	x_column;

	iter = 0;
	x_column = WIDTH / NUM_THREAD;
	while (iter < NUM_THREAD)
	{
		g_env.limits[iter] = x_column * iter;
		iter++;
	}
	iter = 0;
	x_column = WIDTH_PREVIEW / NUM_THREAD;
	while (iter < NUM_THREAD)
	{
		g_env.limits_prev[iter] = x_column * iter;
		iter++;
	}
}

int		main(int argc, char **argv)
{
	if (argc < 2 || argc > 3)
		return (-1);
	if (argc == 3)
	{
		if (ft_strcmp(argv[2], "-p") != 0)
			return (-1);
		g_env.progress_bar = 1;
		load_file(argv[1]);
	}
	else
		load_file(argv[1]);
	gtk_init(&argc, &argv);
	init_limits();
	init_view();
	init_gtk();
	aa_check();
	spin_button();
	gtk_builder_connect_signals(g_env.build, NULL);
	create_list_of_objects();
	g_env.total = WIDTH * HEIGHT;
	launch_thread();
	launch_preview();
	gtk_widget_show_all(g_env.win);
	gtk_main();
	return (EXIT_SUCCESS);
}
