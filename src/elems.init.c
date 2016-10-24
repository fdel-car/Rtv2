/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elems.init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 17:39:03 by fdel-car          #+#    #+#             */
/*   Updated: 2016/10/24 17:40:02 by fdel-car         ###   ########.fr       */
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
	new.text = NULL;
	return (new);
}
