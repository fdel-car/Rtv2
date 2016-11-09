/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.elems.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 17:51:18 by fdel-car          #+#    #+#             */
/*   Updated: 2016/11/09 04:01:53 by bhuver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	push_obj(t_obj *new)
{
	t_obj	*c;

	c = g_env.scene.obj;
	if (c)
		while (c->next)
			c = c->next;
	if (!c)
		g_env.scene.obj = new;
	else
		c->next = new;
}

void	push_to_obj(t_obj *new, t_obj *mesh_node)
{
	t_obj	*c;

	c = mesh_node;
	if (c)
		c = c->lst;
	while (c && c->next)
		c = c->next;
	if (!c)
		mesh_node->lst = new;
	else
		c->next = new;
}

void	push_lgt(t_light *new)
{
	t_light	*c;

	c = g_env.scene.lgt;
	if (c)
		while (c->next)
			c = c->next;
	if (!c)
		g_env.scene.lgt = new;
	else
		c->next = new;
}
