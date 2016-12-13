/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_f10.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 19:56:32 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/13 19:56:33 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	save_entry_material_object2(t_gtkdata *data, float *ret_f,
	int *ret_i, GtkEntry *entry)
{
	if (ft_strcmp(data->desc, "shiny") == 0)
	{
		*ret_f = ft_atof(gtk_entry_get_text(entry));
		((t_obj *)data->obj)->mater.shiny = *ret_f;
	}
	if (ft_strcmp(data->desc, "refl") == 0)
	{
		*ret_f = ft_atof(gtk_entry_get_text(entry));
		((t_obj *)data->obj)->mater.int_refl = *ret_f;
	}
	if (ft_strcmp(data->desc, "trans") == 0)
	{
		*ret_f = ft_atof(gtk_entry_get_text(entry));
		((t_obj *)data->obj)->mater.int_trans = *ret_f;
	}
	if (ft_strcmp(data->desc, "colr") == 0)
	{
		*ret_i = ft_atoi(gtk_entry_get_text(entry));
		((t_obj *)data->obj)->mater.color.r = *ret_i;
	}
}

void	save_entry_material_object3(t_gtkdata *data, char **ret_s,
	int *ret_i, GtkEntry *entry)
{
	if (ft_strcmp(data->desc, "colg") == 0)
	{
		*ret_i = ft_atoi(gtk_entry_get_text(entry));
		((t_obj *)data->obj)->mater.color.g = *ret_i;
	}
	if (ft_strcmp(data->desc, "colb") == 0)
	{
		*ret_i = ft_atoi(gtk_entry_get_text(entry));
		((t_obj *)data->obj)->mater.color.b = *ret_i;
	}
	if (ft_strcmp(data->desc, "text") == 0)
	{
		*ret_s = (char *)gtk_entry_get_text(entry);
	}
}

void	save_entry_material_object4(t_obj *list, t_gtkdata *data)
{
	if (ft_strcmp(data->desc, "shiny") == 0)
	{
		list->mater.shiny = ((t_obj *)data->obj)->mater.shiny;
	}
	if (ft_strcmp(data->desc, "refl") == 0)
	{
		list->mater.int_refl = ((t_obj *)data->obj)->mater.int_refl;
	}
	if (ft_strcmp(data->desc, "trans") == 0)
	{
		list->mater.int_trans = ((t_obj *)data->obj)->mater.int_trans;
	}
	if (ft_strcmp(data->desc, "colr") == 0)
	{
		list->mater.color.r = ((t_obj *)data->obj)->mater.color.r;
	}
	if (ft_strcmp(data->desc, "colg") == 0)
	{
		list->mater.color.g = ((t_obj *)data->obj)->mater.color.g;
	}
}

void	save_entry_material_object(GtkEntry *entry, t_gtkdata *data)
{
	float	ret_f;
	int		ret_i;
	char	*ret_s;
	t_obj	*list;
	short	type;

	type = ((t_obj *)data->obj)->type;
	list = ((t_obj *)data->obj)->lst;
	save_entry_material_object2(data, &ret_f, &ret_i, entry);
	save_entry_material_object3(data, &ret_s, &ret_i, entry);
	if (type == MESH)
	{
		while (list)
		{
			save_entry_material_object4(list, data);
			if (ft_strcmp(data->desc, "colb") == 0)
			{
				list->mater.color.b = ((t_obj *)data->obj)->mater.color.b;
			}
			list = list->next;
		}
	}
}
