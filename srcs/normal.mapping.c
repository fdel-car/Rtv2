/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.mapping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:25:32 by fdel-car          #+#    #+#             */
/*   Updated: 2016/11/25 16:28:18 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vect	bump_normal(t_color p)
{
	t_vect	r;

	r.x = (float)p.r / 255;
	r.y = (float)p.g / 255;
	r.z = (float)p.b / 255;
	r = vec_sub(vec_mult(r, 2.0), vec_new(1, 1, 1));
	return (r);
}
