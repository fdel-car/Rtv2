/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_f3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 19:12:54 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/13 19:12:55 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_gtk_filter_widget(void)
{
	GtkWidget	*combo;
	static char	*combo_text[] = {"None", "Sepia", "Cartoon", "Greyscale",
	"Stereocopique", "Oculus"};
	int			i;

	i = 0;
	combo = GTK_WIDGET(gtk_builder_get_object(g_env.build, "filtre_combo"));
	while (i < 6)
	{
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo),
		combo_text[i]);
		i++;
	}
	gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);
	g_signal_connect(combo, "changed",
			G_CALLBACK(switch_filter), NULL);
}

void	init_gtk_create_widget(void)
{
	GtkWidget	*combo;
	static char	*combo_text[] = {"Sphere", "Plan", "Cone", "Cylindre",
	"Torus", "ADN"};
	int			i;

	i = 0;
	combo = GTK_WIDGET(gtk_builder_get_object(g_env.build, "create_type"));
	while (i < 6)
	{
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo),
				combo_text[i]);
		i++;
	}
}

t_obj	*add_object_type(char *s, t_obj *obj)
{
	if (!s)
		obj->type = NONE;
	else if (ft_strcmp("Sphere", s) == 0)
		obj->type = SPHERE;
	else if (ft_strcmp("Plan", s) == 0)
		obj->type = PLANE;
	else if (ft_strcmp("Cone", s) == 0)
		obj->type = CONE;
	else if (ft_strcmp("Cylindre", s) == 0)
		obj->type = CYLINDER;
	else if (ft_strcmp("Torus", s) == 0)
		obj->type = MESH;
	else if (ft_strcmp("ADN", s) == 0)
		obj->type = MESH;
	return (obj);
}

t_obj	*add_object_name(t_obj *obj)
{
	GtkEntry	*name;

	name = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_name"));
	if (ft_strcmp("", gtk_entry_get_text(name)) == 0)
		obj->name = ft_strdup("no name");
	obj->name = ft_strdup(gtk_entry_get_text(name));
	return (obj);
}

t_obj	*add_object_pos(t_obj *obj)
{
	GtkEntry	*posx;
	GtkEntry	*posy;
	GtkEntry	*posz;

	posx = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_posx"));
	posy = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_posy"));
	posz = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_posz"));
	obj->pos.x = ft_atof(gtk_entry_get_text(posx));
	obj->pos.y = ft_atof(gtk_entry_get_text(posy));
	obj->pos.z = ft_atof(gtk_entry_get_text(posz));
	return (obj);
}
