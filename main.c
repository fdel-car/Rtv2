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
	float old_time, ftime;

	gtk->time = clock();
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			put_pixel(gtk, x, y, 100, 100, 100);
			y++;
		}
		x++;
	}
	gtk_image_set_from_pixbuf(GTK_IMAGE(gtk->img), gtk->pix);
	old_time = gtk->time;
	gtk->time = clock();
	ftime = (gtk->time - old_time) / CLOCKS_PER_SEC;
	ft_putnbr(1.0 / ftime);
	ft_putchar('\n');
}

int		main(int argc, char **argv)
{
	gtk = (t_gtk *)malloc(sizeof(t_gtk));
    gtk_init(&argc, &argv);
    gtk->win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(gtk->win), "Raytracer");
	gtk_window_set_default_size(GTK_WINDOW(gtk->win), WIDTH, HEIGHT);
	gtk_window_set_position(GTK_WINDOW(gtk->win), GTK_WIN_POS_CENTER);
	g_signal_connect(G_OBJECT(gtk->win), "delete-event",
	G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(gtk->win), "key_press_event",
	G_CALLBACK(raytracing), NULL);
	gtk->pix = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, WIDTH, HEIGHT);
	gtk->img = gtk_image_new_from_pixbuf(gtk->pix);
	gtk->grid = gtk_grid_new();
	gtk->list = gtk_list_box_new();
	gtk_grid_attach(GTK_GRID(gtk->grid), gtk->list, 0, 0, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(gtk->grid), gtk->img, gtk->list,
	GTK_POS_RIGHT, 1, 1);

	gtk_container_add(GTK_CONTAINER(gtk->win), gtk->grid);

	gtk->pixels = gdk_pixbuf_get_pixels(gtk->pix);
	gtk->rowstride = WIDTH * 3;
	raytracing();
	gtk_widget_show_all(gtk->win);
	gtk_main();
	free(gtk);
    return EXIT_SUCCESS;
}
