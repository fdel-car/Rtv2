/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_f14.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 12:15:12 by slgracie          #+#    #+#             */
/*   Updated: 2016/12/14 12:15:13 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	position_widget1(t_norm *me, char *s_entry, t_obj *current_obj)
{
	me->entry_posx = malloc(sizeof(t_gtkdata));
	me->entry_posy = malloc(sizeof(t_gtkdata));
	me->entry_posz = malloc(sizeof(t_gtkdata));
	sprintf(s_entry, "%f", current_obj->pos.x);
	me->buffer_pos[0] = gtk_entry_buffer_new(s_entry, ft_strlen(s_entry));
	sprintf(s_entry, "%f", current_obj->pos.y);
	me->buffer_pos[1] = gtk_entry_buffer_new(s_entry, ft_strlen(s_entry));
	sprintf(s_entry, "%f", current_obj->pos.z);
	me->buffer_pos[2] = gtk_entry_buffer_new(s_entry, ft_strlen(s_entry));
	me->label = gtk_label_new("    Position     ");
	me->pos_entry[0] = gtk_entry_new_with_buffer(me->buffer_pos[0]);
	me->pos_entry[1] = gtk_entry_new_with_buffer(me->buffer_pos[1]);
	me->pos_entry[2] = gtk_entry_new_with_buffer(me->buffer_pos[2]);
}

void	position_widget2(t_norm *me, GtkWidget *grid, t_obj *current_obj)
{
	gtk_entry_set_width_chars((GtkEntry *)me->pos_entry[0], 6);
	gtk_entry_set_width_chars((GtkEntry *)me->pos_entry[1], 6);
	gtk_entry_set_width_chars((GtkEntry *)me->pos_entry[2], 6);
	gtk_entry_set_max_length((GtkEntry *)me->pos_entry[0], 6);
	gtk_entry_set_max_length((GtkEntry *)me->pos_entry[1], 6);
	gtk_entry_set_max_length((GtkEntry *)me->pos_entry[2], 6);
	gtk_grid_attach(GTK_GRID(grid), me->label, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->pos_entry[0], 1, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->pos_entry[1], 2, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->pos_entry[2], 3, 0, 1, 1);
	me->entry_posx->data = me->pos_entry[0];
	me->entry_posx->desc = ft_strdup("posx");
	me->entry_posx->obj = current_obj;
	me->entry_posy->data = me->pos_entry[1];
	me->entry_posy->desc = ft_strdup("posy");
	me->entry_posy->obj = current_obj;
	me->entry_posz->data = me->pos_entry[2];
	me->entry_posz->desc = ft_strdup("posz");
	me->entry_posz->obj = current_obj;
}

void	position_widget(t_obj *current_obj, GtkWidget *grid, char *s_entry)
{
	t_norm	me;

	position_widget1(&me, s_entry, current_obj);
	position_widget2(&me, grid, current_obj);
	g_signal_connect(me.pos_entry[0], "changed",
			G_CALLBACK(save_entry_transformation_object), me.entry_posx);
	g_signal_connect(me.pos_entry[1], "changed",
			G_CALLBACK(save_entry_transformation_object), me.entry_posy);
	g_signal_connect(me.pos_entry[2], "changed",
			G_CALLBACK(save_entry_transformation_object), me.entry_posz);
	g_signal_connect(me.pos_entry[0], "changed",
			G_CALLBACK(launch_preview), me.entry_posx);
	g_signal_connect(me.pos_entry[1], "changed",
			G_CALLBACK(launch_preview), me.entry_posy);
	g_signal_connect(me.pos_entry[2], "changed",
			G_CALLBACK(launch_preview), me.entry_posz);
}
