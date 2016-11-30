/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhuver <bhuver@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 01:56:57 by bhuver            #+#    #+#             */
/*   Updated: 2016/11/30 05:40:22 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rgb_to_hsv(t_color rgb)
{
	int			rp;
	int			gp;
	int			bp;
	int			cmax;
	int			cmin;
	int			delta;
	t_color		hsv;

	rp = rgb.r / 255;
	gp = rgb.g / 255;
	bp = rgb.b / 255;
	cmax = (rp > gp) ? rp : gp;
	cmax = (gp > bp) ? gp : bp;
	cmin = (rp < gp) ? rp : gp;
	cmin = (gp < bp) ? gp : bp;
	delta = cmax - cmin;
	if (cmax == rp)
		hsv.r = ((gp - bp) / delta) % 6;
	else if (cmax == gp)
		hsv.r = ((bp - rp) / delta) + 2;
	else if (cmax == bp)
		hsv.r = ((rp - gp) / delta) + 4;
	hsv.g = (cmax == 0) ? 0 : delta / cmax;
}

int		g_pos(guchar *new, int x, int y)
{
	int	pos;

	pos = y * g_env.rowstride + x * 3;
	if (new[pos])
		return ((new[pos] + new[pos + 1] + new[pos + 2]) / 3);
	return (0);
}

void	put_pixel_filter(int x, int y, t_color color)
{
	int	pos;

	pos = y * g_env.rowstride + x * 3;
	g_env.filter_p[pos] = color.r;
	g_env.filter_p[pos + 1] = color.g;
	g_env.filter_p[pos + 2] = color.b;
}

void	sobel_filter(void)
{
	int			x, y;
	t_color		res;
	int			testx, testy, val;

	y = -1;
	while (++y < HEIGHT - 1)
	{
		x = -1;
		while (++x < WIDTH - 1)
		{

			testx = abs((g_pos(g_env.pixels, x - 1, y -1) + 4 *
			g_pos(g_env.pixels, x, y - 1) + g_pos(g_env.pixels, x + 1, y - 1)) -
			(g_pos(g_env.pixels, x - 1, y + 1) + 4 * g_pos(g_env.pixels, x, y +
			1) + g_pos(g_env.pixels, x + 1, y + 1)));
			testy = abs((g_pos(g_env.pixels, x + 1, y - 1) + 4 *
			g_pos(g_env.pixels, x + 1, y) + g_pos(g_env.pixels, x + 1, y + 1)) -
			(g_pos(g_env.pixels, x - 1, y - 1) + 4 * g_pos(g_env.pixels, x - 1,
			y) + g_pos(g_env.pixels, x - 1, y + 1)));
			val = abs(testx) + abs(testy);
			val = 255 - val;
			val > 255 ? val = 255 : val;
			val < 150 ? val = 0 : val;
			res = color_new(val, val, val);
			if (val > 100)
				res = get_color_img(g_env.pixels, x, y, 0, 0);
			put_pixel_filter(x, y, res);
		}
	}
	gtk_image_set_from_pixbuf(GTK_IMAGE(g_env.img), g_env.filter);
}
