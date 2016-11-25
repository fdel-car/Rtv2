/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 19:02:37 by fdel-car          #+#    #+#             */
/*   Updated: 2016/11/25 17:26:24 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	spin_button(void)
{
	GtkAdjustment *adjust;

	if (g_env.scene.iter_refl >= 10)
		g_env.scene.iter_refl = 10;
	if (g_env.scene.iter_refl < 0)
	{
		g_env.scene.iter_refl = 0;
	}
	adjust = gtk_adjustment_new(g_env.scene.iter_refl,
	0.0, 10.0, 1.0, 5.0, 0.0);
	gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(g_env.spin_refl), adjust);
}

void	update_iter_refl(void)
{
	g_env.scene.iter_refl =
	gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(g_env.spin_refl));
}

void	aa_check(void)
{
	if (g_env.scene.anti_alia >= 16)
	{
		g_env.scene.anti_alia = 16;
		gtk_combo_box_set_active(GTK_COMBO_BOX(g_env.aa_choice), 4);
	}
	else if (g_env.scene.anti_alia >= 8 && g_env.scene.anti_alia < 16)
	{
		g_env.scene.anti_alia = 8;
		gtk_combo_box_set_active(GTK_COMBO_BOX(g_env.aa_choice), 3);
	}
	else if (g_env.scene.anti_alia >= 4 && g_env.scene.anti_alia < 8)
	{
		g_env.scene.anti_alia = 4;
		gtk_combo_box_set_active(GTK_COMBO_BOX(g_env.aa_choice), 2);
	}
	else if (g_env.scene.anti_alia >= 2 && g_env.scene.anti_alia < 4)
	{
		g_env.scene.anti_alia = 2;
		gtk_combo_box_set_active(GTK_COMBO_BOX(g_env.aa_choice), 1);
	}
	else if (g_env.scene.anti_alia < 2)
	{
		g_env.scene.anti_alia = 0;
		gtk_combo_box_set_active(GTK_COMBO_BOX(g_env.aa_choice), 0);
	}
}

void	switch_anti_aliasing(void)
{
	char	*s;
	int		aa;

	s = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(g_env.aa_choice));
	aa = ft_atoi(s);
	g_env.scene.anti_alia = aa;
	free(s);
}

void	set_signal_create_object(void)
{
	GtkWidget *window_popup;
	GtkWidget *button_create_object;
	t_gtkData *entry;

	entry = NULL;
	window_popup = GTK_WIDGET(gtk_builder_get_object(g_env.build,
	"popup_create_object"));
	button_create_object = GTK_WIDGET(gtk_builder_get_object(g_env.build,
	"button_create"));
	entry = malloc(sizeof(t_gtkData));
	entry->data = window_popup;
	entry->desc = NULL;
	entry->obj = NULL;
	g_signal_connect(button_create_object, "clicked",
	G_CALLBACK(create_object), entry);
}

void	set_signal_open_save_scene(void)
{
	GtkWidget *btn_open;
	GtkWidget *btn_save;
	GtkWidget *btn_save_img;

	btn_open = NULL;
	btn_save = NULL;
	btn_save_img = NULL;
	btn_open = GTK_WIDGET(gtk_builder_get_object(g_env.build, "btn_open"));
	btn_save = GTK_WIDGET(gtk_builder_get_object(g_env.build, "btn_save"));
	btn_save_img = GTK_WIDGET(gtk_builder_get_object(g_env.build,
	"btn_save_img"));
	g_signal_connect(btn_open, "clicked", G_CALLBACK(open_scene), NULL);
	g_signal_connect(btn_save, "clicked", G_CALLBACK(save_scene), NULL);
	g_signal_connect(btn_save_img, "clicked",
	G_CALLBACK(save_image_chooser), NULL);
}

void	set_signal_switch_cam(void)
{
	GtkWidget *btn_next;
	GtkWidget *btn_prev;

	btn_next = NULL;
	btn_prev = NULL;
	btn_prev = GTK_WIDGET(gtk_builder_get_object(g_env.build, "cam_prev"));
	btn_next = GTK_WIDGET(gtk_builder_get_object(g_env.build, "cam_next"));
	g_signal_connect(btn_prev, "clicked", G_CALLBACK(switch_cam), NULL);
	g_signal_connect(btn_next, "clicked", G_CALLBACK(switch_cam), NULL);
}
