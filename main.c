/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 17:08:45 by fdel-car          #+#    #+#             */
/*   Updated: 2016/09/08 17:50:45 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	put_pixel(t_gtk * gtk, int x, int y, guchar red, guchar green,
	guchar blue)
{
  int pos;

  pos = y * gtk->rowstride + x * 3;
  gtk->pixels[pos] = red;
  gtk->pixels[pos + 1] = green;
  gtk->pixels[pos + 2] = blue;
}

void	raytracing(void)
{
	int x, y = 0;

	gtk->red = gtk_range_get_value(GTK_RANGE(gtk->red_scale));
	gtk->green = gtk_range_get_value(GTK_RANGE(gtk->green_scale));
	gtk->blue = gtk_range_get_value(GTK_RANGE(gtk->blue_scale));
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			put_pixel(gtk, x, y, gtk->red, gtk->green, gtk->blue);
			y++;
		}
		x++;
	}
	gtk_image_set_from_pixbuf(GTK_IMAGE(gtk->img), gtk->pix);
}

int		main(int argc, char **argv)
{
	gtk = (t_gtk *)malloc(sizeof(t_gtk));
    gtk_init(&argc, &argv);
    gtk->win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(gtk->win), "Raytracer");
	gtk_window_set_position(GTK_WINDOW(gtk->win), GTK_WIN_POS_CENTER);
	g_signal_connect(G_OBJECT(gtk->win), "delete-event",
	G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(gtk->win), "key_press_event",
	G_CALLBACK(raytracing), NULL);
	gtk->pix = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, WIDTH, HEIGHT);
	gtk->img = gtk_image_new_from_pixbuf(gtk->pix);
	gtk->box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk->list = gtk_list_box_new();

	// Sliders
	gtk->red_adjust = gtk_adjustment_new(125.0, 0.0, 255.0, 1.0, 51.0, 0.0);
	gtk->green_adjust = gtk_adjustment_new(125.0, 0.0, 255.0, 1.0, 51.0, 0.0);
	gtk->blue_adjust = gtk_adjustment_new(125.0, 0.0, 255.0, 1.0, 51.0, 0.0);
	gtk->red_scale = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, gtk->red_adjust);
	gtk->green_scale = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, gtk->green_adjust);
	gtk->blue_scale = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, gtk->blue_adjust);
	gtk_scale_set_digits(GTK_SCALE(gtk->red_scale), 0);
	gtk_scale_set_digits(GTK_SCALE(gtk->green_scale), 0);
	gtk_scale_set_digits(GTK_SCALE(gtk->blue_scale), 0);
	gtk_widget_set_size_request(gtk->red_scale, 200, 10);
	gtk_widget_set_size_request(gtk->green_scale, 200, 10);
	gtk_widget_set_size_request(gtk->blue_scale, 200, 10);
	gtk->button = gtk_button_new_with_label("Draw image");
	g_signal_connect(G_OBJECT(gtk->button), "button-press-event",
	G_CALLBACK(raytracing), NULL);

	// List insertion
	gtk->box_red = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_start(GTK_BOX(gtk->box_red), gtk_label_new("Red :"),
	FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(gtk->box_red), gtk->red_scale, FALSE, FALSE, 0);
	gtk->box_green = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_start(GTK_BOX(gtk->box_green), gtk_label_new("Green :"),
	FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(gtk->box_green), gtk->green_scale,
	FALSE, FALSE, 0);
	gtk->box_blue = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_start(GTK_BOX(gtk->box_blue), gtk_label_new("Blue :"),
	FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(gtk->box_blue), gtk->blue_scale,
	FALSE, FALSE, 0);

	gtk_list_box_insert(GTK_LIST_BOX(gtk->list), gtk->box_red, -1);
	gtk_list_box_insert(GTK_LIST_BOX(gtk->list), gtk->box_green, -1);
	gtk_list_box_insert(GTK_LIST_BOX(gtk->list), gtk->box_blue, -1);
	gtk_list_box_insert(GTK_LIST_BOX(gtk->list), gtk->button, -1);

	gtk_box_pack_start(GTK_BOX(gtk->box), gtk->list, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(gtk->box), gtk->img, FALSE, FALSE, 0);
	gtk_container_add(GTK_CONTAINER(gtk->win), gtk->box);
	gtk->pixels = gdk_pixbuf_get_pixels(gtk->pix);
	gtk->rowstride = WIDTH * 3;
	raytracing();
	gtk_widget_show_all(gtk->win);
	gtk_main();
	free(gtk);
    return EXIT_SUCCESS;
}
