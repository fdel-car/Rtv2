/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhuver <bhuver@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 01:56:57 by bhuver            #+#    #+#             */
/*   Updated: 2016/12/14 15:24:45 by bhuver           ###   ########.fr       */
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

static int			limit_color(int col)
{
	if (col <= 0)
		return (0);
	else if (col > 0 && col <= 50)
		return (25);
	else if (col > 50 && col <= 100)
		return (75);
	else if (col > 100 && col <= 200)
		return (150);
	else if (col > 200 && col <= 250)
		return (225);
	else if ((col > 250 && col <= 255) || col > 255)
		return (255);
	else
		return (col);
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
			{
				res = get_color_img(g_env.pixels, xy, 0, 0);
				res = color_new(limit_color(res.r),
								limit_color(res.g), limit_color(res.b));
			}
			put_pixel_filter(xy[0], xy[1], res);
		}
	}
	gtk_image_set_from_pixbuf(GTK_IMAGE(g_env.img), g_env.filter);
}
