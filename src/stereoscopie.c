/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stereoscopie.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhuver <bhuver@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 12:17:18 by bhuver            #+#    #+#             */
/*   Updated: 2016/12/08 19:03:12 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				red_filter(void)
{
	int				x;
	int				y;
	t_color			in;
	t_color			out;

	y = -1;
	while (++y < HEIGHT - 1)
	{
		x = -1;
		while (++x < WIDTH - 1)
		{
			in = get_color_img(g_env.pixels, x, y, 0, 0);
			out = color_new(in.r, 0, 0);
			out.r > 255 ? out.r = 255 : 0;
			out.g > 255 ? out.g = 255 : 0;
			out.b > 255 ? out.b = 255 : 0;
			put_pixel_filter(x, y, out);
		}
	}
}

void				green_blue_filter(void)
{
	int				x;
	int				y;
	t_color			in;
	t_color			in2;
	t_color			out;

	y = -1;
	while (++y < HEIGHT - 1)
	{
		x = -1;
		while (++x < WIDTH - 1)
		{
			in = get_color_img(g_env.pixels, x, y, 0, 0);
			in2 = get_color_img(g_env.filter_p, x, y, 0, 0);
			out = color_new(in2.r, in.g, in.b);
			out.r > 255 ? out.r = 255 : 0;
			out.g > 255 ? out.g = 255 : 0;
			out.b > 255 ? out.b = 255 : 0;
			put_pixel_filter(x, y, out);
		}
	}
}

void				stereoscopique_filter(void)
{
	int				x;
	int				y;
	t_color			in;
	t_color			out;

	y = -1;
	while (++y < HEIGHT - 1)
	{
		x = -1;
		while (++x < WIDTH - 1)
		{
			in = get_color_img(g_env.pixels, x, y, 0, 0);
			out = color_new(in.r, 0, 0);
			out.r > 255 ? out.r = 255 : 0;
			out.g > 255 ? out.g = 255 : 0;
			out.b > 255 ? out.b = 255 : 0;
			put_pixel_filter(x, y, out);
		}
	}
	gtk_image_set_from_pixbuf(GTK_IMAGE(g_env.img), g_env.filter);
}

void				left_filter(void)
{
	int				x;
	int				y;
	t_color			in;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			in = get_color_img(g_env.pixels, x, y, 0, 0);
			put_pixel_filter(x, y, in);
			x++;
		}
		y++;
	}
}

void				right_filter(void)
{
	int				x;
	int				y;
	t_color			in;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			in = get_color_img(g_env.pixels, x, y, 0, 0);
			put_pixel_filter(x + 640, y, in);
			x++;
		}
		y++;
	}
}
