/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 17:06:31 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/14 15:11:13 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

t_text	*create_board(void)
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

t_text	*create_perlin(int resolution, float index)
{
	t_text	*tex;

	if (!(tex = malloc(sizeof(t_text))))
		return (0);
	tex->tex_h = resolution;
	tex->tex_w = resolution;
	tex->text = (unsigned char *)malloc(sizeof(unsigned char) *
	(resolution * 3 * resolution));
	generate_perlin_tex(tex, index);
	return (tex);
}

int		fill_texture(t_text *tex, FILE *img)
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
	if (!ft_strcmp(path, "perlin"))
		return (create_perlin(600, 20.0));
	if (!end_by(path, ".bmp") || (img = fopen(path, "r")) <= 0)
		return (0);
	if (!(tex = malloc(sizeof(t_text))) && !fclose(img))
		return (0);
	if (fseek(img, 18, SEEK_SET) < 0)
		return (0);
	if (fread(tex->size, sizeof(int), 2, img) <= 0 && !fclose(img))
		return (0);
	init_tex(tex);
	if (fseek(img, 122, SEEK_SET) < 0)
		return (0);
	tex->text = (unsigned char *)malloc(sizeof(unsigned char) *
	(tex->tex_w * 3 * tex->tex_h));
	if (fill_texture(tex, img) < 0 && !fclose(img))
		return (0);
	fclose(img);
	return (tex);
}
