/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_f5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 19:16:20 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/13 19:18:08 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj	*add_object_mater_refl(t_obj *obj)
{
	GtkEntry	*refl;

	refl = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_refl"));
	obj->mater.int_refl = ft_atof(gtk_entry_get_text(refl));
	return (obj);
}

t_obj	*add_object_mater_trans(t_obj *obj)
{
	GtkEntry	*trans;

	trans = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_trans"));
	obj->mater.int_trans = ft_atof(gtk_entry_get_text(trans));
	return (obj);
}

t_obj	*add_object_mater_color(t_obj *obj)
{
	GdkRGBA			*col;
	GtkColorChooser	*e;

	col = malloc(sizeof(GdkRGBA));
	e = GTK_COLOR_CHOOSER(gtk_builder_get_object(g_env.build, "e_color"));
	gtk_color_chooser_get_rgba(e, col);
	obj->mater.color.r = (int)(col->red * 255);
	obj->mater.color.g = (int)(col->green * 255);
	obj->mater.color.b = (int)(col->blue * 255);
	gdk_rgba_free(col);
	return (obj);
}

void	clear_entry_1(void)
{
	GtkEntry	*name;
	GtkEntry	*posx;
	GtkEntry	*posy;
	GtkEntry	*posz;

	name = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_name"));
	posx = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_posx"));
	posy = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_posy"));
	posz = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_posz"));
	gtk_entry_set_text(name, "");
	gtk_entry_set_text(posx, "");
	gtk_entry_set_text(posy, "");
	gtk_entry_set_text(posz, "");
}

void	clear_entry_2(void)
{
	GtkEntry	*dirx;
	GtkEntry	*diry;
	GtkEntry	*dirz;
	GtkEntry	*rayon;

	rayon = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_rayon"));
	dirx = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_dirx"));
	diry = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_diry"));
	dirz = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_dirz"));
	gtk_entry_set_text(rayon, "");
	gtk_entry_set_text(dirx, "");
	gtk_entry_set_text(diry, "");
	gtk_entry_set_text(dirz, "");
}
