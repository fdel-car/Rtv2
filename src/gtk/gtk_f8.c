/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_f8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 19:41:37 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/13 19:41:38 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	create_object(GtkWidget *entry, t_gtkdata *e)
{
	(void)entry;
	gtk_window_present(GTK_WINDOW(e->data));
}

void	save_color_material_light(GtkEntry *entry, t_gtkdata *data)
{
	GdkRGBA	*col;

	col = malloc(sizeof(GdkRGBA));
	gtk_color_chooser_get_rgba((GtkColorChooser*)entry, col);
	if (ft_strcmp(data->desc, "color") == 0)
	{
		((t_light *)data->obj)->color.r = (int)(col->red * 255);
		((t_light *)data->obj)->color.g = (int)(col->green * 255);
		((t_light *)data->obj)->color.b = (int)(col->blue * 255);
	}
	gdk_rgba_free(col);
}

void	save_color_material(GtkEntry *entry, t_gtkdata *data)
{
	GdkRGBA	*col;
	short	type;
	t_obj	*list;

	col = malloc(sizeof(GdkRGBA));
	list = ((t_obj*)data->obj)->lst;
	type = ((t_obj*)data->obj)->type;
	gtk_color_chooser_get_rgba((GtkColorChooser*)entry, col);
	if (ft_strcmp(data->desc, "color") == 0)
	{
		((t_obj *)data->obj)->mater.color.r = (int)(col->red * 255);
		((t_obj *)data->obj)->mater.color.g = (int)(col->green * 255);
		((t_obj *)data->obj)->mater.color.b = (int)(col->blue * 255);
		if (type == MESH)
			while (list)
			{
				list->mater.color.r = ((t_obj*)data->obj)->mater.color.r;
				list->mater.color.g = ((t_obj*)data->obj)->mater.color.g;
				list->mater.color.b = ((t_obj*)data->obj)->mater.color.b;
				list = list->next;
			}
	}
	gdk_rgba_free(col);
}

void	save_indice_ref(GtkSpinButton *btn, t_gtkdata *data)
{
	((t_obj *)data->obj)->mater.indice = gtk_spin_button_get_value(btn);
}

void	save_entry_transformation_light(GtkEntry *entry, t_gtkdata *data)
{
	float ret;

	ret = ft_atof(gtk_entry_get_text(entry));
	if (ft_strcmp(data->desc, "posx") == 0)
		((t_light*)data->obj)->pos.x = ret;
	if (ft_strcmp(data->desc, "posy") == 0)
		((t_light*)data->obj)->pos.y = ret;
	if (ft_strcmp(data->desc, "posz") == 0)
		((t_light*)data->obj)->pos.z = ret;
	if (ft_strcmp(data->desc, "dirx") == 0)
		((t_light*)data->obj)->dir.x = ret;
	if (ft_strcmp(data->desc, "diry") == 0)
		((t_light*)data->obj)->dir.y = ret;
	if (ft_strcmp(data->desc, "dirz") == 0)
		((t_light*)data->obj)->dir.z = ret;
	((t_light*)data->obj)->dir = vec_norm(((t_light *)data->obj)->dir);
	if (ft_strcmp(data->desc, "rayon") == 0)
		((t_light*)data->obj)->rayon = ret;
}
