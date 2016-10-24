/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/20 14:35:40 by fdel-car          #+#    #+#             */
/*   Updated: 2016/07/21 20:31:11 by fdel-car         ###   ########.fr       */
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

void	launch_thread(void)
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
}

int		main(int argc, char **argv)
{
	int iter = 0;
	int	x_column = WIDTH / NUM_THREAD;

	if (argc == 2)
		load_file(argv[1]);
	gtk_init(&argc, &argv);
	while (iter < NUM_THREAD)
	{
		g_env.limits[iter] = x_column * iter;
		iter++;
	}
	// probleme au parsing de la pos de la camera
	// printf("pos :%f, %f, %f\n", g_env.scene.cam.pos.x, g_env.scene.cam.pos.y, g_env.scene.cam.pos.z);
	g_env.scene.cam.pos = vec_new(0, 0, -10);
	init_view();
	g_env.win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(g_env.win), "Raytracer");
	gtk_window_set_position(GTK_WINDOW(g_env.win), GTK_WIN_POS_CENTER);
	g_signal_connect(G_OBJECT(g_env.win), "delete-event",
	G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(g_env.win), "key_press_event",
	G_CALLBACK(launch_thread), NULL);
	g_env.pix = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, WIDTH, HEIGHT);
	g_env.img = gtk_image_new_from_pixbuf(g_env.pix);
	g_env.box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	g_env.list = gtk_list_box_new();
	gtk_box_pack_start(GTK_BOX(g_env.box), g_env.img, FALSE, FALSE, 0);
	gtk_container_add(GTK_CONTAINER(g_env.win), g_env.box);
	g_env.pixels = gdk_pixbuf_get_pixels(g_env.pix);
	g_env.rowstride = WIDTH * 3;
	launch_thread();
	gtk_widget_show_all(g_env.win);
	gtk_main();
	return (EXIT_SUCCESS);
}
