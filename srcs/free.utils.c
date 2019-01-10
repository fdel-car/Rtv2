/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 16:43:50 by vde-la-s          #+#    #+#             */
/*   Updated: 2016/12/13 18:55:56 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	free_text(t_text *t)
{
	if (!t)
		return ;
	free(t->text);
	free(t);
}

void	free_mater(t_mater m)
{
	if (m.tex)
		free_text(m.tex);
	if (m.ntex)
		free_text(m.ntex);
	if (m.ctex)
		free_text(m.ctex);
	if (m.ttex)
		free_text(m.ttex);
}

void	free_objs(t_obj *o)
{
	t_obj	*next;

	next = 0;
	while (o)
	{
		next = o->next;
		if (o->name)
			free(o->name);
		if (o->src)
			free(o->src);
		if (o->lst)
			free_objs(o->lst);
		free_mater(o->mater);
		free(o);
		o = next;
	}
}

void	free_objects(gboolean all)
{
	t_obj	*o;
	t_obj	*tmp;

	o = g_env.scene.obj;
	if (all == FALSE)
		o = o->next;
	while (o)
	{
		tmp = o->next;
		if (o->name)
			free(o->name);
		if (o->src)
			free(o->src);
		if (o->lst)
			free_objs(o->lst);
		free_mater(o->mater);
		free(o);
		o = tmp;
	}
	if (all == FALSE)
		g_env.scene.obj->next = NULL;
	else
		g_env.scene.obj = NULL;
}

void	free_lights(void)
{
	t_light	*l;
	t_light	*tmp;

	l = g_env.scene.lgt;
	while (l)
	{
		tmp = l->next;
		if (l->name)
			free(l->name);
		free(l);
		l = tmp;
	}
	g_env.scene.lgt = NULL;
}
