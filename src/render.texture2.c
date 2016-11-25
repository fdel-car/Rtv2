/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.texture2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 16:55:01 by fdel-car          #+#    #+#             */
/*   Updated: 2016/11/25 16:57:47 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_limit(int v, int min, int max)
{
	v > max ? v = max : 0;
	v < min ? v = min : 0;
	return (v);
}

t_color	get_resize_pxl(t_text *tex, float coef, int x, int y)
{
	t_color	c;
	int		old_x;
	int		old_y;
	int		pos;

	old_x = x / coef;
	old_y = y / coef;
	pos = old_y * tex->tex_w * 3 + old_x * 3;
	c.r = tex->text[pos];
	c.g = tex->text[pos + 1];
	c.b = tex->text[pos + 2];
	return (c);
}

void	resize_texture(t_text *tex, float coef)
{
	unsigned char	*tmp;
	int				x;
	int				x_max;
	int				y;
	int				y_max;
	int				pos;
	t_color			c;

	if (!tex)
		return ;
	x_max = tex->tex_w * coef;
	y_max = tex->tex_h * coef;
	tmp = (unsigned char *)malloc(sizeof(unsigned char) * x_max * 3 * y_max);
	pos = 0;
	y = 0;
	while (y < y_max)
	{
		x = 0;
		while (x < x_max)
		{
			c = get_resize_pxl(tex, coef, x, y);
			tmp[pos++] = c.r;
			tmp[pos++] = c.g;
			tmp[pos++] = c.b;
			x++;
		}
		y++;
	}
	free(tex->text);
	tex->text = tmp;
	tex->tex_w = x_max;
	tex->tex_h = y_max;
}
