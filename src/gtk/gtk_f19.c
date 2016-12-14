/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_f19.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 12:08:18 by slgracie          #+#    #+#             */
/*   Updated: 2016/12/14 12:08:20 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	create_transformation_wl1(t_norm *me,
char *s_entry, t_light *current_light)
{
	me->entry_posx = malloc(sizeof(t_gtkdata));
	me->entry_posy = malloc(sizeof(t_gtkdata));
	me->entry_posz = malloc(sizeof(t_gtkdata));
	me->entry_rayon = malloc(sizeof(t_gtkdata));
	sprintf(s_entry, "%f", current_light->pos.x);
	me->buffer_pos[0] = gtk_entry_buffer_new(s_entry, ft_strlen(s_entry));
	sprintf(s_entry, "%f", current_light->pos.y);
	me->buffer_pos[1] = gtk_entry_buffer_new(s_entry, ft_strlen(s_entry));
	sprintf(s_entry, "%f", current_light->pos.z);
	me->buffer_pos[2] = gtk_entry_buffer_new(s_entry, ft_strlen(s_entry));
	sprintf(s_entry, "%f", current_light->rayon);
	me->buffer_rayon = gtk_entry_buffer_new(s_entry, ft_strlen(s_entry));
	me->mlabel[0] = gtk_label_new("    Position    ");
	me->mlabel[2] = gtk_label_new("Rayon");
	me->pos_entry[0] = gtk_entry_new_with_buffer(me->buffer_pos[0]);
	me->pos_entry[1] = gtk_entry_new_with_buffer(me->buffer_pos[1]);
	me->pos_entry[2] = gtk_entry_new_with_buffer(me->buffer_pos[2]);
	me->rayon_entry = gtk_entry_new_with_buffer(me->buffer_rayon);
}

void	create_transformation_wl2(t_norm *me,
t_light *current_light, GtkWidget *grid, char *s_entry)
{
	direction_widget_light(current_light, grid, s_entry);
	gtk_entry_set_width_chars((GtkEntry *)me->pos_entry[0], 6);
	gtk_entry_set_width_chars((GtkEntry *)me->pos_entry[1], 6);
	gtk_entry_set_width_chars((GtkEntry *)me->pos_entry[2], 6);
	gtk_entry_set_width_chars((GtkEntry *)me->rayon_entry, 6);
	gtk_entry_set_max_length((GtkEntry *)me->pos_entry[0], 6);
	gtk_entry_set_max_length((GtkEntry *)me->pos_entry[1], 6);
	gtk_entry_set_max_length((GtkEntry *)me->pos_entry[2], 6);
	gtk_entry_set_max_length((GtkEntry *)me->rayon_entry, 6);
	gtk_grid_attach(GTK_GRID(grid), me->mlabel[0], 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->mlabel[2], 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->pos_entry[0], 1, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->pos_entry[1], 2, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->pos_entry[2], 3, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->rayon_entry, 1, 2, 1, 1);
}

void	create_transformation_wl3(t_norm *me)
{
	g_signal_connect(me->pos_entry[0], "changed",
			G_CALLBACK(save_entry_transformation_light), me->entry_posx);
	g_signal_connect(me->pos_entry[1], "changed",
			G_CALLBACK(save_entry_transformation_light), me->entry_posy);
	g_signal_connect(me->pos_entry[2], "changed",
			G_CALLBACK(save_entry_transformation_light), me->entry_posz);
	g_signal_connect(me->rayon_entry, "changed",
			G_CALLBACK(save_entry_transformation_light), me->entry_rayon);
	g_signal_connect(me->pos_entry[0], "changed",
			G_CALLBACK(launch_preview), me->entry_posx);
	g_signal_connect(me->pos_entry[1], "changed",
			G_CALLBACK(launch_preview), me->entry_posy);
	g_signal_connect(me->pos_entry[2], "changed",
			G_CALLBACK(launch_preview), me->entry_posz);
	g_signal_connect(me->rayon_entry, "changed",
			G_CALLBACK(launch_preview), me->entry_rayon);
}

void	create_transformation_widget_light(void *object, GtkWidget *grid)
{
	t_light		*current_light;
	char		*s_entry;
	t_norm		me;

	s_entry = malloc(sizeof(char) * 10);
	current_light = (t_light *)object;
	create_transformation_wl1(&me, s_entry, current_light);
	create_transformation_wl2(&me, current_light, grid, s_entry);
	me.entry_posx->data = me.pos_entry[0];
	me.entry_posx->desc = ft_strdup("posx");
	me.entry_posx->obj = current_light;
	me.entry_posy->data = me.pos_entry[1];
	me.entry_posy->desc = ft_strdup("posy");
	me.entry_posy->obj = current_light;
	me.entry_posz->data = me.pos_entry[2];
	me.entry_posz->desc = ft_strdup("posz");
	me.entry_posz->obj = current_light;
	me.entry_rayon->data = me.rayon_entry;
	me.entry_rayon->desc = ft_strdup("rayon");
	me.entry_rayon->obj = current_light;
	create_transformation_wl3(&me);
}
