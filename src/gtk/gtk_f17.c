/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_f17.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 12:12:08 by slgracie          #+#    #+#             */
/*   Updated: 2016/12/14 12:12:10 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rayon_widget(t_obj *current_obj, GtkWidget *grid, char *s_entry)
{
	GtkWidget		*label;
	GtkWidget		*rayon_entry;
	GtkEntryBuffer	*buffer_rayon;
	t_gtkdata		*entry_rayon;

	entry_rayon = malloc(sizeof(t_gtkdata));
	sprintf(s_entry, "%f", current_obj->rayon);
	buffer_rayon = gtk_entry_buffer_new(s_entry, ft_strlen(s_entry));
	label = gtk_label_new("Rayon");
	rayon_entry = gtk_entry_new_with_buffer(buffer_rayon);
	gtk_entry_set_width_chars((GtkEntry *)rayon_entry, 6);
	gtk_entry_set_max_length((GtkEntry *)rayon_entry, 6);
	gtk_grid_attach(GTK_GRID(grid), label, 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), rayon_entry, 1, 2, 1, 1);
	entry_rayon->data = rayon_entry;
	entry_rayon->desc = ft_strdup("rayon");
	entry_rayon->obj = current_obj;
	g_signal_connect(rayon_entry, "changed",
			G_CALLBACK(save_entry_transformation_object), entry_rayon);
	g_signal_connect(rayon_entry, "changed",
			G_CALLBACK(launch_preview), entry_rayon);
}

void	alpha_widget(t_obj *current_obj, GtkWidget *grid, char *s_entry)
{
	GtkWidget			*label;
	GtkWidget			*alpha_entry;
	GtkEntryBuffer		*buffer_alpha;
	t_gtkdata			*entry_alpha;

	entry_alpha = malloc(sizeof(t_gtkdata));
	sprintf(s_entry, "%f", current_obj->alpha);
	buffer_alpha = gtk_entry_buffer_new(s_entry, ft_strlen(s_entry));
	label = gtk_label_new("Alpha");
	alpha_entry = gtk_entry_new_with_buffer(buffer_alpha);
	gtk_entry_set_width_chars((GtkEntry *)alpha_entry, 6);
	gtk_entry_set_max_length((GtkEntry *)alpha_entry, 6);
	gtk_grid_attach(GTK_GRID(grid), label, 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), alpha_entry, 1, 2, 1, 1);
	entry_alpha->data = alpha_entry;
	entry_alpha->desc = ft_strdup("alpha");
	entry_alpha->obj = current_obj;
	g_signal_connect(alpha_entry, "changed",
			G_CALLBACK(save_entry_transformation_object), entry_alpha);
	g_signal_connect(alpha_entry, "changed",
			G_CALLBACK(launch_preview), entry_alpha);
}

void	create_transformation_widget_object(void *object, GtkWidget *grid)
{
	t_obj	*current_obj;
	char	*s_entry;

	s_entry = malloc(sizeof(char) * 10);
	current_obj = (t_obj *)object;
	position_widget(current_obj, grid, s_entry);
	if (current_obj->type == CONE || current_obj->type == CYLINDER)
		direction_widget(current_obj, grid, s_entry);
	if (current_obj->type == CYLINDER || current_obj->type == SPHERE)
		rayon_widget(current_obj, grid, s_entry);
	if (current_obj->type == PLANE)
		normal_widget(current_obj, grid, s_entry);
	if (current_obj->type == CONE)
		alpha_widget(current_obj, grid, s_entry);
}
