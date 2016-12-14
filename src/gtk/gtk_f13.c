/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_f13.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 12:16:20 by slgracie          #+#    #+#             */
/*   Updated: 2016/12/14 13:24:29 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	create_materw_light1(t_norm *me, char *s_entry, t_light *current_obj)
{
	me->entry_intensity = malloc(sizeof(t_gtkdata));
	me->entry_col_r = malloc(sizeof(t_gtkdata));
	me->entry_col_g = malloc(sizeof(t_gtkdata));
	me->entry_col_b = malloc(sizeof(t_gtkdata));
	me->entry_col = malloc(sizeof(t_gtkdata));
	sprintf(s_entry, "%f", current_obj->intensity);
	me->intensity_buffer = gtk_entry_buffer_new(s_entry, ft_strlen(s_entry));
	sprintf(s_entry, "%d", current_obj->color.r);
	me->color_r_buffer = gtk_entry_buffer_new(s_entry, ft_strlen(s_entry));
	sprintf(s_entry, "%d", current_obj->color.g);
	me->color_g_buffer = gtk_entry_buffer_new(s_entry, ft_strlen(s_entry));
	sprintf(s_entry, "%d", current_obj->color.b);
	me->color_b_buffer = gtk_entry_buffer_new(s_entry, ft_strlen(s_entry));
	free(s_entry);
	me->intensity_label = gtk_label_new("    Intensite    ");
	me->color_label = gtk_label_new("Color");
	me->intensity_entry = gtk_entry_new_with_buffer(me->intensity_buffer);
	me->color_r_entry = gtk_entry_new_with_buffer(me->color_r_buffer);
}

void	create_materw_light2(t_norm *me, t_light *current_obj,
GtkWidget *grid, GdkRGBA *col)
{
	me->color_g_entry = gtk_entry_new_with_buffer(me->color_g_buffer);
	me->color_b_entry = gtk_entry_new_with_buffer(me->color_b_buffer);
	col->red = (double)current_obj->color.r / 255;
	col->green = (double)current_obj->color.g / 255;
	col->blue = (double)current_obj->color.b / 255;
	col->alpha = 1;
	me->color_button = gtk_color_button_new_with_rgba((const GdkRGBA *)col);
	me->entry_col->data = me->color_button;
	me->entry_col->desc = ft_strdup("color");
	me->entry_col->obj = current_obj;
	gtk_entry_set_width_chars((GtkEntry *)me->intensity_entry, 6);
	gtk_entry_set_width_chars((GtkEntry *)me->color_r_entry, 3);
	gtk_entry_set_width_chars((GtkEntry *)me->color_g_entry, 3);
	gtk_entry_set_width_chars((GtkEntry *)me->color_b_entry, 3);
	gtk_entry_set_max_length((GtkEntry *)me->intensity_entry, 6);
	gtk_entry_set_max_length((GtkEntry *)me->color_r_entry, 3);
	gtk_entry_set_max_length((GtkEntry *)me->color_g_entry, 3);
	gtk_entry_set_max_length((GtkEntry *)me->color_b_entry, 3);
	gtk_grid_attach(GTK_GRID(grid), me->intensity_label, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->color_label, 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->intensity_entry, 1, 0, 1, 1);
}

void	create_materw_light3(t_norm *me, t_light *current_obj,
GtkWidget *grid)
{
	gtk_grid_attach(GTK_GRID(grid), me->color_r_entry, 1, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->color_g_entry, 2, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->color_b_entry, 3, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->color_button, 4, 2, 1, 1);
	me->entry_intensity->data = me->intensity_entry;
	me->entry_intensity->desc = ft_strdup("intens");
	me->entry_intensity->obj = current_obj;
	me->entry_col_r->data = me->color_r_entry;
	me->entry_col_r->desc = ft_strdup("colr");
	me->entry_col_r->obj = current_obj;
	me->entry_col_g->data = me->color_g_entry;
	me->entry_col_g->desc = ft_strdup("colg");
	me->entry_col_g->obj = current_obj;
	me->entry_col_b->data = me->color_b_entry;
	me->entry_col_b->desc = ft_strdup("colb");
	me->entry_col_b->obj = current_obj;
	g_signal_connect(me->intensity_entry, "changed",
			G_CALLBACK(save_entry_material_light), me->entry_intensity);
}

void	create_materw_light4(t_norm *me)
{
	g_signal_connect(me->color_r_entry, "changed",
			G_CALLBACK(save_entry_material_light), me->entry_col_r);
	g_signal_connect(me->color_g_entry, "changed",
			G_CALLBACK(save_entry_material_light), me->entry_col_g);
	g_signal_connect(me->color_b_entry, "changed",
			G_CALLBACK(save_entry_material_light), me->entry_col_b);
	g_signal_connect(me->intensity_entry, "changed",
			G_CALLBACK(launch_preview), me->entry_intensity);
	g_signal_connect(me->color_r_entry, "changed",
			G_CALLBACK(launch_preview), me->entry_col_r);
	g_signal_connect(me->color_g_entry, "changed",
			G_CALLBACK(launch_preview), me->entry_col_g);
	g_signal_connect(me->color_b_entry, "changed",
			G_CALLBACK(launch_preview), me->entry_col_b);
	g_signal_connect(me->color_button, "color-set",
			G_CALLBACK(save_color_material_light), me->entry_col);
	g_signal_connect(me->color_button, "color-set",
			G_CALLBACK(launch_preview), me->entry_col);
}

void	create_material_widget_light(void *object, GtkWidget *grid)
{
	t_light		*current_obj;
	char		*s_entry;
	t_norm		me;
	GdkRGBA		*col;

	col = malloc(sizeof(GdkRGBA));
	me.entry_intensity = NULL;
	me.entry_col_r = NULL;
	me.entry_col_g = NULL;
	me.entry_col_b = NULL;
	me.entry_col = NULL;
	s_entry = malloc(sizeof(char) * 10);
	current_obj = (t_light *)object;
	create_materw_light1(&me, s_entry, current_obj);
	create_materw_light2(&me, current_obj, grid, col);
	create_materw_light3(&me, current_obj, grid);
	create_materw_light4(&me);
}
