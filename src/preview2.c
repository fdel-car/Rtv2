/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preview2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 16:40:32 by fdel-car          #+#    #+#             */
/*   Updated: 2016/11/25 16:41:07 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		put_pixel_prev(int x, int y, t_color color)
{
	int pos;

	pos = y * g_env.rowstride_prev + x * 3;
	g_env.pixels_prev[pos] = color.r;
	g_env.pixels_prev[pos + 1] = color.g;
	g_env.pixels_prev[pos + 2] = color.b;
}
