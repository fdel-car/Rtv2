/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elems.init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 17:39:03 by fdel-car          #+#    #+#             */
/*   Updated: 2016/11/23 15:04:42 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_mater		init_mater(void)
{
	t_mater	new;

	new.shiny = 0;
	new.int_refl = 0;
	new.int_trans = 0;
	new.color = color_new(0, 0, 0);
	new.tex = NULL;
	new.ntex = NULL;
	return (new);
}
