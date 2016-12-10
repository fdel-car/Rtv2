/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 22:20:34 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/10 17:18:36 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	add_sphere(t_obj *o, t_vect pos)
{
	t_obj *sp;
	sp = malloc(sizeof(t_obj));
	init_obj(sp);
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

	pos = vec_new(o->pos.x + o->rayon, o->pos.y, o->pos.z);
	while (i < 360)
	{
		add_sphere(o, pos);
		pos = rot_any(pos, o->dir, 1);
		i++;
	}
}

void	add_sphere_adn(t_obj *o, t_vect pos)
{
	t_obj *sp;

	sp = malloc(sizeof(t_obj));
	init_obj(sp);
	sp->next = NULL;
	sp->src = NULL;
	sp->name = "sphere";
	sp->cut = vec_new(0, 0, 0);
	sp->min = 0;
	sp->max = 0;
	sp->pos = pos;
	sp->rayon = 0.3;
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

void	add_cylindre_adn(t_obj *o, t_vect pos, t_vect pos1)
{
	t_obj *sp;

	sp = malloc(sizeof(t_obj));
	init_obj(sp);
	sp->next = NULL;
	sp->src = NULL;
	sp->name = "tic";
	sp->cut = vec_new(0, 0, 0);
	sp->min = - (o->rayon);
	sp->max = o->rayon;
	sp->pos = vec_new(pos.x, pos.y,pos.z);
	sp->dir = vec_norm(vec_sub(pos, pos1));
	sp->rayon = 0.12;
	sp->type = CYLINDER;
	sp->mater.shiny = o->mater.shiny;
	sp->mater.int_refl = o->mater.int_refl;
	sp->mater.int_trans = o->mater.int_trans;
	sp->mater.color = color_new(o->mater.color.g,o->mater.color.b,o->mater.color.r);
	sp->mater.tex = o->mater.tex;
	sp->mater.ntex = o->mater.ntex;
	sp->mater.indice = o->mater.indice;
	sp->lst = NULL;
	sp->func = &intersect_cylinder;
	push_to_obj(sp, o);
}
void	add_adn(t_obj *o)
{
	t_vect	pos;
	t_vect	pos1;
	int		i = 0;


	pos = vec_new(o->pos.x + o->rayon, o->pos.y, o->pos.z);
	pos1 = vec_new(o->pos.x - o->rayon, o->pos.y, o->pos.z);
	while (i < 18)
	{
		pos.y += 0.8;
		pos1.y += 0.8;
		add_sphere_adn(o, pos);
		add_sphere_adn(o, pos1);
		add_cylindre_adn(o,pos, pos1);
		pos = rot_y(20, pos);
		pos1 = rot_y(20, pos1);
		i++;
	}
}
