/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhuver <bhuver@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 01:45:38 by bhuver            #+#    #+#             */
/*   Updated: 2016/12/12 13:16:12 by bhuver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color		get_color_img(guchar *new, int *xy, int i, int j)
{
	t_color			color;
	int				pos;

	pos = (xy[1] + j) * g_env.rowstride + (xy[0] + i) * 3;
	if (new[pos])
	{
		color.r = new[pos];
		color.g = new[pos + 1];
		color.b = new[pos + 2];
		return (color);
	}
	return (color_new(0, 0, 0));
}

void		sepia_filter(void)
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
			out = color_new((in.r * 0.393) + (in.g * 0.769) + (in.b * 0.189),
			(in.r * 0.349) + (in.g * 0.686) + (in.b * 0.168),
			(in.r * 0.272) + (in.g * 0.534) + (in.b * 0.131));
			out.r > 255 ? out.r = 255 : 0;
			out.g > 255 ? out.g = 255 : 0;
			out.b > 255 ? out.b = 255 : 0;
			put_pixel_filter(xy[0], xy[1], out);
		}
	}
	gtk_image_set_from_pixbuf(GTK_IMAGE(g_env.img), g_env.filter);
}

t_color		greyscale(t_color c)
{
	t_color			new;

	new.r = (c.r + c.g + c.b) / 3;
	new.g = new.r;
	new.b = new.r;
	return (new);
}

void		greyscale_filter(void)
{
	int				xy[2];
	t_color			out;

	xy[1] = -1;
	while (++xy[1] < HEIGHT - 1)
	{
		xy[0] = -1;
		while (++xy[0] < WIDTH - 1)
		{
			out = greyscale(get_color_img(g_env.pixels, xy, 0, 0));
			put_pixel_filter(xy[0], xy[1], out);
		}
	}
	gtk_image_set_from_pixbuf(GTK_IMAGE(g_env.img), g_env.filter);
}
