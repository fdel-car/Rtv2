/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 15:37:11 by fdel-car          #+#    #+#             */
/*   Updated: 2016/10/24 15:37:14 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color		color_new(int r, int g, int b)
{
	t_color new;

	new.r = r;
	new.g = g;
	new.b = b;
	return (new);
}

t_color		color_mult(t_color color, float value)
{
	t_color rgb;

	rgb.r = color.r * value;
	if (rgb.r > 255)
		rgb.r = 255;
	rgb.g = color.g * value;
	if (rgb.g > 255)
		rgb.g = 255;
	rgb.b = color.b * value;
	if (rgb.b > 255)
		rgb.b = 255;
	return (rgb);
}

t_color		color_add(t_color u, t_color v)
{
	t_color rgb;

	rgb.r = u.r + v.r;
	if (rgb.r > 255)
		rgb.r = 255;
	rgb.g = u.g + v.g;
	if (rgb.g > 255)
		rgb.g = 255;
	rgb.b = u.b + v.b;
	if (rgb.b > 255)
		rgb.b = 255;
	return (rgb);
}

t_color		color_stack(t_color u, t_color v)
{
	t_color rgb;

	rgb.r = u.r + v.r;
	rgb.g = u.g + v.g;
	rgb.b = u.b + v.b;
	return (rgb);
}

t_color		color_sub(t_color u, t_color v)
{
	t_color rgb;

	rgb.r = u.r - v.r;
	if (rgb.r < 0)
		rgb.r = 0;
	rgb.g = u.g - v.g;
	if (rgb.g < 0)
		rgb.g = 0;
	rgb.b = u.b - v.b;
	if (rgb.b < 0)
		rgb.b = 0;
	return (rgb);
}
