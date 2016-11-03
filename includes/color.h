/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 15:41:29 by fdel-car          #+#    #+#             */
/*   Updated: 2016/10/24 15:41:32 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

t_color		color_new(int r, int g, int b);
t_color		color_mult(t_color color, float value);
t_color		color_stack(t_color u, t_color v);
t_color		color_add(t_color u, t_color v);
t_color		color_sub(t_color u, t_color v);

#endif
