/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhuver <bhuver@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 01:56:57 by bhuver            #+#    #+#             */
/*   Updated: 2016/12/12 13:07:52 by bhuver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int					g_pos(guchar *new, int x, int y)
{
	int				pos;

	pos = y * g_env.rowstride + x * 3;
	if (new[pos])
		return ((new[pos] + new[pos + 1] + new[pos + 2]) / 3);
	return (0);
}

void				put_pixel_filter(int x, int y, t_color color)
{
	int				pos;

	pos = y * g_env.rowstride + x * 3;
	g_env.filter_p[pos] = color.r;
	g_env.filter_p[pos + 1] = color.g;
	g_env.filter_p[pos + 2] = color.b;
}

static t_color		high_sat(t_color in)
{
	t_color			out;

	out = color_new(in.r * 0.80, in.g * 0.80, in.b * 0.80);
	if (in.r >= in.g && in.r >= in.b)
		out.r = in.r * 1.20;
	if (in.g >= in.r && in.g >= in.b)
		out.g = in.g * 1.20;
	if (in.b >= in.g && in.b >= in.r)
		out.b = in.b * 1.20;
	out.r > 255 ? out.r = 255 : 0;
	out.g > 255 ? out.g = 255 : 0;
	out.b > 255 ? out.b = 255 : 0;
	return (out);
}

static int			sobel_compute(int x, int y)
{
	int				sobel;

	sobel = abs((g_pos(g_env.pixels, x - 1, y - 1) +
				4 * g_pos(g_env.pixels, x, y - 1) +
				g_pos(g_env.pixels, x + 1, y - 1)) -
				(g_pos(g_env.pixels, x - 1, y + 1) +
				4 * g_pos(g_env.pixels, x, y + 1) +
				g_pos(g_env.pixels, x + 1, y + 1))) +
		abs((g_pos(g_env.pixels, x + 1, y - 1) +
			4 * g_pos(g_env.pixels, x + 1, y) +
			g_pos(g_env.pixels, x + 1, y + 1)) -
			(g_pos(g_env.pixels, x - 1, y - 1) +
			4 * g_pos(g_env.pixels, x - 1, y) +
			g_pos(g_env.pixels, x - 1, y + 1)));
	return (sobel);
}

void				sobel_filter(void)
{
	int				xy[2];
	int				sobel;
	t_color			res;

	xy[1] = -1;
	while (++xy[1] < HEIGHT - 1)
	{
		xy[0] = -1;
		while (++xy[0] < WIDTH - 1)
		{
			sobel = sobel_compute(xy[0], xy[1]);
			sobel = 255 - sobel;
			sobel > 255 ? sobel = 255 : sobel;
			sobel < 150 ? sobel = 0 : sobel;
			res = color_new(sobel, sobel, sobel);
			if (sobel > 100)
				res = high_sat(get_color_img(g_env.pixels, xy, 0, 0));
			put_pixel_filter(xy[0], xy[1], res);
		}
	}
	gtk_image_set_from_pixbuf(GTK_IMAGE(g_env.img), g_env.filter);
}
