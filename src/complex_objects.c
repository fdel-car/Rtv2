/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 22:20:34 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/15 12:26:42 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	add_sphere(t_obj *o, t_vect pos)
{
	t_obj	*sp;

	sp = malloc(sizeof(t_obj));
	init_obj(sp);
	sp->next = NULL;
	sp->src = NULL;
	sp->name = ft_strdup("sphere");
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
	int		i;

	i = 0;
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
	sp->name = ft_strdup("tic");
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

void	add_cylindre_adn(t_obj *o, t_vect pos, t_vect pos2)
{
	t_obj	*sp;

	sp = malloc(sizeof(t_obj));
	init_obj(sp);
	sp->next = NULL;
	sp->src = NULL;
	sp->name = ft_strdup("tac");
	sp->cut = vec_new(0, 0, 0);
	sp->min = -(o->rayon);
	sp->max = o->rayon;
	sp->pos = pos;
	sp->dir = vec_norm(vec_sub(pos, pos2));
	sp->rayon = 0.12;
	sp->type = CYLINDER;
	sp->mater.shiny = o->mater.shiny;
	sp->mater.int_refl = o->mater.int_refl;
	sp->mater.int_trans = o->mater.int_trans;
	sp->mater.color = color_new(o->mater.color.g, o->mater.color.b,
	o->mater.color.r);
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
	t_vect	pos2;
	int		i;

	i = 0;
	if (vec_dotp(o->dir, o->norm) != 0)
		return ;
	pos = vec_mult(o->norm, o->rayon);
	pos2 = vec_mult(o->norm, -o->rayon);
	while (i < 18)
	{
		pos = vec_add(pos, vec_mult(o->dir, 0.8));
		pos2 = vec_add(pos2, vec_mult(o->dir, 0.8));
		add_sphere_adn(o, pos);
		add_sphere_adn(o, pos2);
		add_cylindre_adn(o, pos, pos2);
		pos = rot_any(pos, o->dir, 20);
		pos2 = rot_any(pos2, o->dir, 20);
		i++;
	}
}
