/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 17:06:31 by fdel-car          #+#    #+#             */
/*   Updated: 2016/11/16 00:46:00 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	test_texture(t_text tex)
{
	t_color color;
	int x = 0;
	int y;
	while (x < tex.tex_w)
	{
		y = 0;
		while (y < tex.tex_h)
		{
			color.r = tex.text[y * (tex.tex_w * 3) + (x * 3)];
			color.g = tex.text[y * (tex.tex_w * 3) + (x * 3) + 1];
			color.b = tex.text[y * (tex.tex_w * 3) + (x * 3) + 2];
			put_pixel(x, y, color);
			y++;
		}
		x++;
	}
	gtk_image_set_from_pixbuf(GTK_IMAGE(g_env.img), g_env.pix);
}

t_text	*load_texture(char *path)
{
	FILE	*img;
	t_text	*tex;
	int		iter;
	int		tmp;
	int		tmp2;

	iter = 0;
	if (!(img = fopen(path, "r")))
		return (0);
	tex = malloc(sizeof(t_text));
	fseek(img, 18, SEEK_SET);
	fread(tex->size, sizeof(int), 2, img);
	tex->tex_w = tex->size[0];
	tex->tex_h = tex->size[1];
	fseek(img, 122, SEEK_SET);
	tex->text = (unsigned char *)malloc(sizeof(unsigned char) *
	(tex->tex_w * 3 * tex->tex_h));
	tmp = tex->tex_w * 3 * tex->tex_h - 1;
	while (iter++ < tex->tex_h)
	{
		tmp2 = 0;
		while (tmp2++ < tex->tex_w)
		{
			fread(tex->buff, 1, 3, img);
			tex->text[tmp--] = tex->buff[0];
			tex->text[tmp--] = tex->buff[1];
			tex->text[tmp--] = tex->buff[2];
		}
	}
	fclose(img);
	return (tex);
}
