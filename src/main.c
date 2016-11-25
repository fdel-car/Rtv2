/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/20 14:35:40 by fdel-car          #+#    #+#             */
/*   Updated: 2016/11/22 18:06:39 by fdel-car         ###   ########.fr       */
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

void	pre_compute_tri(void)
{
	t_obj *o;
	t_obj *tmp;

	o = g_env.scene.obj;
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

void	launch_thread(void)
{
	desactivate_preview();
	// g_env.pixels_progress = 0;
	// g_env.progress = 0;
	g_env.scene.cam.right = cross_pr(g_env.scene.cam.up, g_env.scene.cam.dir);
	g_env.scene.cam.up = cross_pr(g_env.scene.cam.dir, g_env.scene.cam.right);
	g_env.scene.cam.up_left = vec_add(g_env.scene.cam.pos,
	vec_add(vec_mult(g_env.scene.cam.dir, g_env.scene.cam.view_d),
	vec_sub(vec_mult(g_env.scene.cam.up, (g_env.scene.cam.view_h / 2.0)),
	vec_mult(g_env.scene.cam.right, (g_env.scene.cam.view_w / 2.0)))));
	pre_compute_tri();
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
	gtk_image_set_from_pixbuf(GTK_IMAGE(g_env.img), g_env.pix);
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

void	init_gtk(void)
{
	static char *anti_alia[] = {"None", "2x AA", "4x AA", "8x AA", "16x AA"};
	int			iter;

	iter = 0;
	g_env.build = gtk_builder_new_from_file("interface.glade");
	g_env.win = GTK_WIDGET(gtk_builder_get_object(g_env.build, "win"));
	g_env.pix = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, WIDTH, HEIGHT);
	g_env.pix_prev = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8,
			WIDTH_PREVIEW, HEIGHT_PREVIEW);
	g_env.img = GTK_WIDGET(gtk_builder_get_object(g_env.build, "final_img"));
	g_env.prev = GTK_WIDGET(gtk_builder_get_object(g_env.build, "prev_img"));
	g_env.aa_choice = GTK_WIDGET(gtk_builder_get_object(g_env.build,
				"aa_choice"));
	g_env.spin_refl = GTK_WIDGET(gtk_builder_get_object(g_env.build,
				"spin_refl"));
	g_env.toggle_prev = GTK_WIDGET(gtk_builder_get_object(g_env.build,
				"prev_button"));
	g_env.pixels = gdk_pixbuf_get_pixels(g_env.pix);
	g_env.pixels_prev = gdk_pixbuf_get_pixels(g_env.pix_prev);
	g_env.rowstride = WIDTH * 3;
	g_env.rowstride_prev = WIDTH_PREVIEW * 3;
	g_env.state_prev = FALSE;
	while (iter < 5)
	{
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(g_env.aa_choice),
				anti_alia[iter]);
		iter++;
	}
	init_gtk_create_widget();
	set_signal_create_object();
	set_signal_open_save_scene();
	set_signal_switch_cam();
}

int		main(int argc, char **argv)
{
	if (argc < 2 || argc > 3)
		return (-1);
	load_file(argv[1]);
	if (argc == 3)
	{
		if (strcmp(argv[2],"-p") == 0)
			g_env.progress_bar = 1;
		else
			g_env.progress_bar = 1;
	}
	load_file(argv[1]);
	gtk_init(&argc, &argv);
	init_limits();
	init_view();
	init_gtk();
	aa_check();
	spin_button();
	gtk_builder_connect_signals(g_env.build, NULL);
	create_list_of_objects();
	// g_object_unref(g_env.build);
	g_env.total = WIDTH * HEIGHT;
	launch_thread();
	launch_preview();
	gtk_widget_show_all(g_env.win);
	gtk_main();
	return (EXIT_SUCCESS);
}
