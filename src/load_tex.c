/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 17:06:31 by fdel-car          #+#    #+#             */
/*   Updated: 2016/11/23 13:57:10 by vde-la-s         ###   ########.fr       */
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

void	fill_board(t_text *tex, int curs[2], t_color cl[2], int ref)
{
	int		i_c;
	t_color	r;

	i_c = 0;
	while (curs[0]++ < tex->tex_h)
	{
		if (!(curs[0] % 1))
			i_c = i_c == 0 ? 1 : 0;
		curs[1] = 0;
		while (curs[1]++ < tex->tex_w)
		{
			if (!(curs[1] % 1))
				i_c = i_c == 0 ? 1 : 0;
			r = cl[i_c];
			tex->text[ref--] = r.b;
			tex->text[ref--] = r.g;
			tex->text[ref--] = r.r;
		}
	}
}

t_text	*create_board()
{
	t_text	*tex;
	int		ref;
	int		curs[2];
	t_color	cl[2];

	if (!(tex = malloc(sizeof(t_text))))
		return (0);
	cl[0] = color_new(0, 0, 0);
	cl[1] = color_new(200, 200, 200);
	tex->tex_h = 10;
	tex->tex_w = 10;
	tex->text = (unsigned char *)malloc(sizeof(unsigned char) *
	(tex->tex_w * 3 * tex->tex_h));
	ref = tex->tex_w * 3 * tex->tex_h - 1;
	curs[0] = 0;
	fill_board(tex, curs, cl, ref);
	return (tex);
}

int	fill_texture(t_text *tex, FILE	*img)
{
	int		iter;
	int		tmp;
	int		tmp2;

	iter = 0;
	tmp = tex->tex_w * 3 * tex->tex_h - 1;
	while (iter++ < tex->tex_h)
	{
		tmp2 = 0;
		while (tmp2++ < tex->tex_w)
		{
			if (fread(tex->buff, 1, 3, img) <= 0)
				return (-1);
			tex->text[tmp--] = tex->buff[0];
			tex->text[tmp--] = tex->buff[1];
			tex->text[tmp--] = tex->buff[2];
		}
	}
	return (1);
}

t_text	*load_texture(char *path)
{
	FILE	*img;
	t_text	*tex;

	if (!ft_strcmp(path, "damier"))
		return (create_board());
	if (!end_by(path, ".bmp") || (img = fopen(path, "r")) <= 0)
		return (0);
	if (!(tex = malloc(sizeof(t_text))) && !fclose(img))
		return (0);
	if (fseek(img, 18, SEEK_SET) < 0)
		return (0);
	if (fread(tex->size, sizeof(int), 2, img) <= 0 && !fclose(img))
		return (0);
	tex->tex_w = tex->size[0];
	tex->tex_h = tex->size[1];
	if (fseek(img, 122, SEEK_SET) < 0)
		return (0);
	tex->text = (unsigned char *)malloc(sizeof(unsigned char) *
	(tex->tex_w * 3 * tex->tex_h));
	if (fill_texture(tex, img) < 0 && !fclose(img))
		return (0);
	fclose(img);
	return (tex);
}
