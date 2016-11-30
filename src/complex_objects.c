/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 22:20:34 by fdel-car          #+#    #+#             */
/*   Updated: 2016/11/30 00:25:39 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	add_sphere(t_obj *o, t_vect pos)
{
	t_obj *sp;

	sp = malloc(sizeof(t_obj));
	sp->next = NULL;
	sp->src = NULL;
	sp->name = "sphere";
	sp->cut = vec_new(0, 0, 0);
	sp->min = 0;
	sp->max = 0;
	sp->pos = pos;
	sp->rayon = 1.0;
	sp->type = SPHERE;
	sp->mater.shiny = o->mater.shiny;
	sp->mater.int_refl = o->mater.int_refl;
	sp->mater.int_trans = o->mater.int_trans;
	sp->mater.color = o->mater.color;
	sp->mater.tex = o->mater.tex;
	sp->mater.ntex = o->mater.ntex;
	sp->mater.indice = o->mater.indice;
	sp->lst = NULL;
	sp->func = &intersect_sphere;
	push_to_obj(sp, o);
}

void	add_torus_sphere(t_obj *o)
{
	t_vect	pos;
	int		i = 0;

	pos = vec_new(o->rayon, 0, 0);
	while (i < 360)
	{
		add_sphere(o, pos);
		pos = rot_y(1, pos);
		i++;
	}
}
