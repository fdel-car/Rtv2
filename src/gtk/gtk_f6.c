/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_f6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 19:32:36 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/14 12:49:26 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	clear_entry_3(void)
{
	GtkEntry	*normx;
	GtkEntry	*normy;
	GtkEntry	*normz;
	GtkEntry	*alpha;

	alpha = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_angle"));
	normx = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_normx"));
	normy = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_normy"));
	normz = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_normz"));
	gtk_entry_set_text(normx, "");
	gtk_entry_set_text(normy, "");
	gtk_entry_set_text(normz, "");
	gtk_entry_set_text(alpha, "");
}

void	clear_entry_4(void)
{
	GtkEntry	*shiny;
	GtkEntry	*refl;
	GtkEntry	*trans;

	trans = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_trans"));
	refl = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_refl"));
	shiny = GTK_ENTRY(gtk_builder_get_object(g_env.build, "e_shiny"));
	gtk_entry_set_text(shiny, "");
	gtk_entry_set_text(refl, "");
	gtk_entry_set_text(trans, "");
}

void	clear_entry_widget_add_object(void)
{
	clear_entry_1();
	clear_entry_2();
	clear_entry_3();
	clear_entry_4();
}

void	signal_add_object2(t_obj *obj, char *s)
{
	if (!s)
		;
	else if (ft_strcmp(s, "Torus") == 0)
		add_torus_sphere(obj);
	else if (ft_strcmp(s, "ADN") == 0)
		add_adn(obj);
	push_obj(obj);
	clear_entry_widget_add_object();
	gtk_widget_hide(GTK_WIDGET(gtk_builder_get_object(g_env.build,
	"popup_create_object")));
	create_list_of_objects();
	launch_preview();
	launch_thread();
}

void	signal_add_object(void)
{
	char	*s;
	t_obj	*obj;

	obj = 0;
	s = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(\
		gtk_builder_get_object(g_env.build, "create_type")));
	obj = malloc(sizeof(t_obj));
	init_obj(obj);
	add_object_type(s, obj);
	obj = add_object_name(obj);
	obj = add_object_pos(obj);
	obj = add_object_dir(obj);
	obj = add_object_norm(obj);
	obj = add_object_rayon(obj);
	obj = add_object_alpha(obj);
	obj = add_object_mater_shiny(obj);
	obj = add_object_mater_refl(obj);
	obj = add_object_mater_trans(obj);
	obj = add_object_mater_color(obj);
	obj->next = NULL;
	obj->mater.tex = NULL;
	set_func(obj);
	signal_add_object2(obj, s);
}
