/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.elems.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 17:50:09 by fdel-car          #+#    #+#             */
/*   Updated: 2016/10/24 17:50:10 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	print_obj(void)
{
	t_obj	*c;

	printf("objs\n");
	c = g_env.scene.obj;
	while (c)
	{
		printf("name: %s\n", c->name);
		printf("pos: %f %f %f\n", c->pos.x, c->pos.y, c->pos.z);
		printf("rayon: %f\n", c->rayon);
		printf("color: %d %d %d\n", c->mater.color.r, c->mater.color.g,
		c->mater.color.b);
		c = c->next;
	}
	printf("---------\n");
}

void	print_lgt(void)
{
	t_light	*c;

	c = g_env.scene.lgt;
	while (c)
	{
		printf("name: %s\n", c->name);
		printf("pos: %f %f %f\n", c->pos.x, c->pos.y, c->pos.z);
		printf("----\n");
		c = c->next;
	}
	printf("---------\n");
}
