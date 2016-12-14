/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_f18.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 12:10:15 by slgracie          #+#    #+#             */
/*   Updated: 2016/12/14 12:10:32 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	direction_widgetl1(t_norm *me, char *s_entry, t_light *current_obj)
{
	me->entry_dirx = malloc(sizeof(t_gtkdata));
	me->entry_diry = malloc(sizeof(t_gtkdata));
	me->entry_dirz = malloc(sizeof(t_gtkdata));
	sprintf(s_entry, "%f", current_obj->dir.x);
	me->buffer_dir[0] = gtk_entry_buffer_new(s_entry, ft_strlen(s_entry));
	sprintf(s_entry, "%f", current_obj->dir.y);
	me->buffer_dir[1] = gtk_entry_buffer_new(s_entry, ft_strlen(s_entry));
	sprintf(s_entry, "%f", current_obj->dir.z);
	me->buffer_dir[2] = gtk_entry_buffer_new(s_entry, ft_strlen(s_entry));
	me->label = gtk_label_new("Direction");
	me->dir_entry[0] = gtk_entry_new_with_buffer(me->buffer_dir[0]);
	me->dir_entry[1] = gtk_entry_new_with_buffer(me->buffer_dir[1]);
	me->dir_entry[2] = gtk_entry_new_with_buffer(me->buffer_dir[2]);
}

void	direction_widgetl2(t_norm *me, GtkWidget *grid, t_light *current_obj)
{
	gtk_entry_set_width_chars((GtkEntry *)me->dir_entry[0], 6);
	gtk_entry_set_width_chars((GtkEntry *)me->dir_entry[1], 6);
	gtk_entry_set_width_chars((GtkEntry *)me->dir_entry[2], 6);
	gtk_entry_set_max_length((GtkEntry *)me->dir_entry[0], 6);
	gtk_entry_set_max_length((GtkEntry *)me->dir_entry[1], 6);
	gtk_entry_set_max_length((GtkEntry *)me->dir_entry[2], 6);
	gtk_grid_attach(GTK_GRID(grid), me->label, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->dir_entry[0], 1, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->dir_entry[1], 2, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->dir_entry[2], 3, 1, 1, 1);
	me->entry_dirx->data = me->dir_entry[0];
	me->entry_dirx->desc = ft_strdup("dirx");
	me->entry_dirx->obj = current_obj;
	me->entry_diry->data = me->dir_entry[1];
	me->entry_diry->desc = ft_strdup("diry");
	me->entry_diry->obj = current_obj;
	me->entry_dirz->data = me->dir_entry[2];
	me->entry_dirz->desc = ft_strdup("dirz");
	me->entry_dirz->obj = current_obj;
}

void	direction_widget_light(t_light *current_obj,
		GtkWidget *grid, char *s_entry)
{
	t_norm	me;

	direction_widgetl1(&me, s_entry, current_obj);
	direction_widgetl2(&me, grid, current_obj);
	g_signal_connect(me.dir_entry[0], "changed",
			G_CALLBACK(save_entry_transformation_object), me.entry_dirx);
	g_signal_connect(me.dir_entry[1], "changed",
			G_CALLBACK(save_entry_transformation_object), me.entry_diry);
	g_signal_connect(me.dir_entry[2], "changed",
			G_CALLBACK(save_entry_transformation_object), me.entry_dirz);
	g_signal_connect(me.dir_entry[0], "changed",
			G_CALLBACK(launch_preview), me.entry_dirx);
	g_signal_connect(me.dir_entry[1], "changed",
			G_CALLBACK(launch_preview), me.entry_diry);
	g_signal_connect(me.dir_entry[2], "changed",
			G_CALLBACK(launch_preview), me.entry_dirz);
}
