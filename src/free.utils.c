/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 16:43:50 by vde-la-s          #+#    #+#             */
/*   Updated: 2016/12/13 16:50:01 by vde-la-s         ###   ########.fr       */
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

void	free_lgts(t_light *l)
{
	while (l)
	{
		if (l->name)
			free(l->name);
		l = l->next;
	}
}

void free_genv(void)
{
	free(g_env.scene.name);
	free_objs(g_env.scene.obj);
	free_lgts(g_env.scene.lgt);
}
