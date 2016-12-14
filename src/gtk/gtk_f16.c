/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_f16.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 12:13:01 by slgracie          #+#    #+#             */
/*   Updated: 2016/12/14 12:13:48 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	normal_widget1(t_norm *me, char *s_entry, t_obj *current_obj)
{
	me->entry_normx = malloc(sizeof(t_gtkdata));
	me->entry_normy = malloc(sizeof(t_gtkdata));
	me->entry_normz = malloc(sizeof(t_gtkdata));
	sprintf(s_entry, "%f", current_obj->norm.x);
	me->buffer_norm[0] = gtk_entry_buffer_new(s_entry, ft_strlen(s_entry));
	sprintf(s_entry, "%f", current_obj->norm.y);
	me->buffer_norm[1] = gtk_entry_buffer_new(s_entry, ft_strlen(s_entry));
	sprintf(s_entry, "%f", current_obj->norm.z);
	me->buffer_norm[2] = gtk_entry_buffer_new(s_entry, ft_strlen(s_entry));
	me->label = gtk_label_new("Normal");
	me->norm_entry[0] = gtk_entry_new_with_buffer(me->buffer_norm[0]);
	me->norm_entry[1] = gtk_entry_new_with_buffer(me->buffer_norm[1]);
	me->norm_entry[2] = gtk_entry_new_with_buffer(me->buffer_norm[2]);
}

void	normal_widget2(t_norm *me, GtkWidget *grid, t_obj *current_obj)
{
	gtk_entry_set_width_chars((GtkEntry *)me->norm_entry[0], 6);
	gtk_entry_set_width_chars((GtkEntry *)me->norm_entry[1], 6);
	gtk_entry_set_width_chars((GtkEntry *)me->norm_entry[2], 6);
	gtk_entry_set_max_length((GtkEntry *)me->norm_entry[0], 6);
	gtk_entry_set_max_length((GtkEntry *)me->norm_entry[1], 6);
	gtk_entry_set_max_length((GtkEntry *)me->norm_entry[2], 6);
	gtk_grid_attach(GTK_GRID(grid), me->label, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->norm_entry[0], 1, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->norm_entry[1], 2, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->norm_entry[2], 3, 1, 1, 1);
	me->entry_normx->data = me->norm_entry[0];
	me->entry_normx->desc = ft_strdup("normx");
	me->entry_normx->obj = current_obj;
	me->entry_normy->data = me->norm_entry[1];
	me->entry_normy->desc = ft_strdup("normy");
	me->entry_normy->obj = current_obj;
	me->entry_normz->data = me->norm_entry[2];
	me->entry_normz->desc = ft_strdup("normz");
	me->entry_normz->obj = current_obj;
}

void	normal_widget(t_obj *current_obj, GtkWidget *grid, char *s_entry)
{
	t_norm	me;

	normal_widget1(&me, s_entry, current_obj);
	normal_widget2(&me, grid, current_obj);
	g_signal_connect(me.norm_entry[0], "changed",
			G_CALLBACK(save_entry_transformation_object), me.entry_normx);
	g_signal_connect(me.norm_entry[1], "changed",
			G_CALLBACK(save_entry_transformation_object), me.entry_normy);
	g_signal_connect(me.norm_entry[2], "changed",
			G_CALLBACK(save_entry_transformation_object), me.entry_normz);
	g_signal_connect(me.norm_entry[0], "changed",
			G_CALLBACK(launch_preview), me.entry_normx);
	g_signal_connect(me.norm_entry[1], "changed",
			G_CALLBACK(launch_preview), me.entry_normy);
	g_signal_connect(me.norm_entry[2], "changed",
			G_CALLBACK(launch_preview), me.entry_normz);
}
