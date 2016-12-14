/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.texture2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 16:55:01 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/14 14:12:44 by vde-la-s         ###   ########.fr       */
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

void	resize_texture_init(int xy_max[2],
t_text *tex, unsigned char *tmp, float coef)
{
	xy_max[0] = tex->tex_w * coef;
	xy_max[1] = tex->tex_h * coef;
	tmp = (unsigned char *)malloc(sizeof(unsigned char)
	* xy_max[0] * 3 * xy_max[1]);
}

void	resize_texture_exit(t_text *tex,
unsigned char *tmp, int xy_max[2])
{
	free(tex->text);
	tex->text = tmp;
	tex->tex_w = xy_max[0];
	tex->tex_h = xy_max[1];
}

void	resize_texture(t_text *tex, float coef)
{
	unsigned char	*tmp;
	int				xy[2];
	int				xy_max[2];
	int				pos;
	t_color			c;

	if (!(tmp = 0) && !tex)
		return ;
	resize_texture_init(xy_max, tex, tmp, coef);
	pos = 0;
	xy[1] = 0;
	while (xy[1] < xy_max[1])
	{
		xy[0] = 0;
		while (xy[0] < xy_max[0])
		{
			c = get_resize_pxl(tex, coef, xy[0], xy[1]);
			tmp[pos++] = c.r;
			tmp[pos++] = c.g;
			tmp[pos++] = c.b;
			xy[0]++;
		}
		xy[1]++;
	}
	resize_texture_exit(tex, tmp, xy_max);
}
