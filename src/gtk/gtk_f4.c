/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_f4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 19:14:57 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/13 19:14:58 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj	*add_object_dir(t_obj *obj)
{
	GtkEntry	*dirx;
	GtkEntry	*diry;
	GtkEntry	*dirz;

	dirx = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_dirx"));
	diry = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_diry"));
	dirz = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_dirz"));
	obj->dir.x = ft_atof(gtk_entry_get_text(dirx));
	obj->dir.y = ft_atof(gtk_entry_get_text(diry));
	obj->dir.z = ft_atof(gtk_entry_get_text(dirz));
	obj->dir = vec_norm(obj->dir);
	return (obj);
}

t_obj	*add_object_norm(t_obj *obj)
{
	GtkEntry	*normx;
	GtkEntry	*normy;
	GtkEntry	*normz;

	normx = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_normx"));
	normy = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_normy"));
	normz = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_normz"));
	obj->norm.x = ft_atof(gtk_entry_get_text(normx));
	obj->norm.y = ft_atof(gtk_entry_get_text(normy));
	obj->norm.z = ft_atof(gtk_entry_get_text(normz));
	obj->norm = vec_norm(obj->norm);
	return (obj);
}

t_obj	*add_object_rayon(t_obj *obj)
{
	GtkEntry	*rayon;

	rayon = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_rayon"));
	obj->rayon = ft_atof(gtk_entry_get_text(rayon));
	return (obj);
}

t_obj	*add_object_alpha(t_obj *obj)
{
	GtkEntry	*alpha;

	alpha = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_angle"));
	obj->alpha = ft_atof(gtk_entry_get_text(alpha)) * M_PI / 180;
	return (obj);
}

t_obj	*add_object_mater_shiny(t_obj *obj)
{
	GtkEntry	*shiny;

	shiny = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_shiny"));
	obj->mater.shiny = ft_atof(gtk_entry_get_text(shiny));
	return (obj);
}
