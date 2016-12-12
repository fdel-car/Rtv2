/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stereoscopie.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhuver <bhuver@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 12:17:18 by bhuver            #+#    #+#             */
/*   Updated: 2016/12/12 13:15:50 by bhuver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				red_filter(void)
{
	int				xy[2];
	t_color			in;
	t_color			out;

	xy[1] = -1;
	while (++xy[1] < HEIGHT - 1)
	{
		xy[0] = -1;
		while (++xy[0] < WIDTH - 1)
		{
			in = get_color_img(g_env.pixels, xy, 0, 0);
			out = color_new(in.r, 0, 0);
			out.r > 255 ? out.r = 255 : 0;
			out.g > 255 ? out.g = 255 : 0;
			out.b > 255 ? out.b = 255 : 0;
			put_pixel_filter(xy[0], xy[1], out);
		}
	}
}

void				green_blue_filter(void)
{
	int				xy[2];
	t_color			in;
	t_color			in2;
	t_color			out;

	xy[1] = -1;
	while (++xy[1] < HEIGHT - 1)
	{
		xy[0] = -1;
		while (++xy[0] < WIDTH - 1)
		{
			in = get_color_img(g_env.pixels, xy, 0, 0);
			in2 = get_color_img(g_env.filter_p, xy, 0, 0);
			out = color_new(in2.r, in.g, in.b);
			out.r > 255 ? out.r = 255 : 0;
			out.g > 255 ? out.g = 255 : 0;
			out.b > 255 ? out.b = 255 : 0;
			put_pixel_filter(xy[0], xy[1], out);
		}
	}
}

void				stereoscopique_filter(void)
{
	int				xy[2];
	t_color			in;
	t_color			out;

	xy[1] = -1;
	while (++xy[1] < HEIGHT - 1)
	{
		xy[0] = -1;
		while (++xy[0] < WIDTH - 1)
		{
			in = get_color_img(g_env.pixels, xy, 0, 0);
			out = color_new(in.r, 0, 0);
			out.r > 255 ? out.r = 255 : 0;
			out.g > 255 ? out.g = 255 : 0;
			out.b > 255 ? out.b = 255 : 0;
			put_pixel_filter(xy[0], xy[1], out);
		}
	}
	gtk_image_set_from_pixbuf(GTK_IMAGE(g_env.img), g_env.filter);
}

void				left_filter(void)
{
	int				xy[2];
	t_color			in;

	xy[1] = 0;
	while (xy[1] < HEIGHT)
	{
		xy[0] = 0;
		while (xy[0] < WIDTH)
		{
			in = get_color_img(g_env.pixels, xy, 0, 0);
			put_pixel_filter(xy[0], xy[1], in);
			xy[0]++;
		}
		xy[1]++;
	}
}

void				right_filter(void)
{
	int				xy[2];
	t_color			in;

	xy[1] = 0;
	while (xy[1] < HEIGHT)
	{
		xy[0] = 0;
		while (xy[0] < WIDTH)
		{
			in = get_color_img(g_env.pixels, xy, 0, 0);
			put_pixel_filter(xy[0] + 640, xy[1], in);
			xy[0]++;
		}
		xy[1]++;
	}
}
