/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_f9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 19:47:06 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/15 13:48:25 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	save_translation_mesh_object2(t_obj *list, t_gtkdata *data,
	t_vect oldpos)
{
	if (ft_strcmp(data->desc, "posx") == 0)
	{
		list->v0.x += (((t_obj *)data->obj)->pos.x - oldpos.x);
		list->v1.x += (((t_obj *)data->obj)->pos.x - oldpos.x);
		list->v2.x += (((t_obj *)data->obj)->pos.x - oldpos.x);
	}
	else if (ft_strcmp(data->desc, "posy") == 0)
	{
		list->v0.y += (((t_obj *)data->obj)->pos.y - oldpos.y);
		list->v1.y += (((t_obj *)data->obj)->pos.y - oldpos.y);
		list->v2.y += (((t_obj *)data->obj)->pos.y - oldpos.y);
	}
	else if (ft_strcmp(data->desc, "posz") == 0)
	{
		list->v0.z += (((t_obj *)data->obj)->pos.z - oldpos.z);
		list->v1.z += (((t_obj *)data->obj)->pos.z - oldpos.z);
		list->v2.z += (((t_obj *)data->obj)->pos.z - oldpos.z);
	}
}

void	save_translation_mesh_object3(t_obj *list, t_gtkdata *data,
	t_vect oldpos)
{
	if (ft_strcmp(data->desc, "posx") == 0)
	{
		list->pos.x += (((t_obj *)data->obj)->pos.x - oldpos.x);
	}
	else if (ft_strcmp(data->desc, "posy") == 0)
	{
		list->pos.y += (((t_obj *)data->obj)->pos.y - oldpos.y);
	}
	else if (ft_strcmp(data->desc, "posz") == 0)
	{
		list->pos.z += (((t_obj *)data->obj)->pos.z - oldpos.z);
	}
}

void	save_translation_mesh_object(GtkEntry *entry, t_gtkdata *data,
	t_vect oldpos)
{
	t_obj	*list;
	float	ret;

	list = ((t_obj *)data->obj)->lst;
	ret = ft_atof(gtk_entry_get_text(entry));
	while (list)
	{
		if (list->type == TRIANGLE)
			save_translation_mesh_object2(list, data, oldpos);
		else
			save_translation_mesh_object3(list, data, oldpos);
		list = list->next;
	}
}

void	save_entry_transformation_object2(t_gtkdata *data, float ret)
{
	if (ft_strcmp(data->desc, "posx") == 0)
		((t_obj *)data->obj)->pos.x = ret;
	if (ft_strcmp(data->desc, "posy") == 0)
		((t_obj *)data->obj)->pos.y = ret;
	if (ft_strcmp(data->desc, "posz") == 0)
		((t_obj *)data->obj)->pos.z = ret;
	if (ft_strcmp(data->desc, "dirx") == 0)
		((t_obj *)data->obj)->dir.x = ret;
	if (ft_strcmp(data->desc, "diry") == 0)
		((t_obj *)data->obj)->dir.y = ret;
	if (ft_strcmp(data->desc, "dirz") == 0)
		((t_obj *)data->obj)->dir.z = ret;
	((t_obj *)data->obj)->dir = vec_norm(((t_obj *)data->obj)->dir);
	if (ft_strcmp(data->desc, "normx") == 0)
		((t_obj *)data->obj)->norm.x = ret;
	((t_obj *)data->obj)->norm = vec_norm(((t_obj *)data->obj)->norm);
}

void	save_entry_transformation_object(GtkEntry *entry, t_gtkdata *data)
{
	float	ret;
	t_vect	pos;

	ret = ft_atof(gtk_entry_get_text(entry));
	pos = ((t_obj *)data->obj)->pos;
	save_entry_transformation_object2(data, ret);
	if (ft_strcmp(data->desc, "normy") == 0)
		((t_obj *)data->obj)->norm.y = ret;
	if (ft_strcmp(data->desc, "normz") == 0)
		((t_obj *)data->obj)->norm.z = ret;
	if (ft_strcmp(data->desc, "rayon") == 0)
		((t_obj *)data->obj)->rayon = ret;
	if (ft_strcmp(data->desc, "alpha") == 0)
		((t_obj *)data->obj)->alpha = ret * M_PI / 180;
	if (((t_obj *)data->obj)->type == MESH)
		if (ft_strcmp(data->desc, "posx") == 0 || ft_strcmp(data->desc,
		"posy") == 0 || ft_strcmp(data->desc, "posz") == 0)
			save_translation_mesh_object(entry, data, pos);
}
