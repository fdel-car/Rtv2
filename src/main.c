/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 17:08:45 by fdel-car          #+#    #+#             */
/*   Updated: 2016/10/22 16:33:05 by vde-la-s         ###   ########.fr       */
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

void	raytracing(void)
{
	int x, y = 0;

	g_env.color.r = gtk_range_get_value(GTK_RANGE(g_env.red_scale));
	g_env.color.g = gtk_range_get_value(GTK_RANGE(g_env.green_scale));
	g_env.color.b = gtk_range_get_value(GTK_RANGE(g_env.blue_scale));
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			put_pixel(x, y, g_env.color);
			y++;
		}
		x++;
	}
	gtk_image_set_from_pixbuf(GTK_IMAGE(g_env.img), g_env.pix);
}

int		main(int argc, char **argv)
{
	if (argc == 2)
		load_file(argv[1]);
	print_obj();
	print_lgt();
	gtk_init(&argc, &argv);
	g_env.win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(g_env.win), "Raytracer");
	gtk_window_set_position(GTK_WINDOW(g_env.win), GTK_WIN_POS_CENTER);
	g_signal_connect(G_OBJECT(g_env.win), "delete-event",
	G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(g_env.win), "key_press_event",
	G_CALLBACK(raytracing), NULL);
	g_env.pix = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, WIDTH, HEIGHT);
	g_env.img = gtk_image_new_from_pixbuf(g_env.pix);
	g_env.box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	g_env.list = gtk_list_box_new();

	// Sliders
	g_env.red_adjust = gtk_adjustment_new(125.0, 0.0, 255.0, 1.0, 51.0, 0.0);
	g_env.green_adjust = gtk_adjustment_new(125.0, 0.0, 255.0, 1.0, 51.0, 0.0);
	g_env.blue_adjust = gtk_adjustment_new(125.0, 0.0, 255.0, 1.0, 51.0, 0.0);
	g_env.red_scale = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL,
	g_env.red_adjust);
	g_env.green_scale = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL,
	g_env.green_adjust);
	g_env.blue_scale = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL,
	g_env.blue_adjust);
	gtk_scale_set_digits(GTK_SCALE(g_env.red_scale), 0);
	gtk_scale_set_digits(GTK_SCALE(g_env.green_scale), 0);
	gtk_scale_set_digits(GTK_SCALE(g_env.blue_scale), 0);
	gtk_widget_set_size_request(g_env.red_scale, 200, 10);
	gtk_widget_set_size_request(g_env.green_scale, 200, 10);
	gtk_widget_set_size_request(g_env.blue_scale, 200, 10);
	g_env.button = gtk_button_new_with_label("Draw image");
	g_signal_connect(G_OBJECT(g_env.button), "button-press-event",
	G_CALLBACK(raytracing), NULL);

	g_env.box_red = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_start(GTK_BOX(g_env.box_red), gtk_label_new("Red :"),
	FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(g_env.box_red), g_env.red_scale,
	FALSE, FALSE, 0);
	g_env.box_green = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_start(GTK_BOX(g_env.box_green), gtk_label_new("Green :"),
	FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(g_env.box_green), g_env.green_scale,
	FALSE, FALSE, 0);
	g_env.box_blue = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_start(GTK_BOX(g_env.box_blue), gtk_label_new("Blue :"),
	FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(g_env.box_blue), g_env.blue_scale,
	FALSE, FALSE, 0);

	// List insertion
	gtk_list_box_insert(GTK_LIST_BOX(g_env.list), g_env.box_red, -1);
	gtk_list_box_insert(GTK_LIST_BOX(g_env.list), g_env.box_green, -1);
	gtk_list_box_insert(GTK_LIST_BOX(g_env.list), g_env.box_blue, -1);
	gtk_list_box_insert(GTK_LIST_BOX(g_env.list), g_env.button, -1);

	gtk_box_pack_start(GTK_BOX(g_env.box), g_env.list, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(g_env.box), g_env.img, FALSE, FALSE, 0);
	gtk_container_add(GTK_CONTAINER(g_env.win), g_env.box);
	g_env.pixels = gdk_pixbuf_get_pixels(g_env.pix);
	g_env.rowstride = WIDTH * 3;
	raytracing();
	gtk_widget_show_all(g_env.win);
	gtk_main();
	return (EXIT_SUCCESS);
}
