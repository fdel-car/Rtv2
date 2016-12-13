#include "rt.h"

void	normal_widget(t_obj *current_obj, GtkWidget *grid,char *s_entry)
{
	GtkWidget *label;
	GtkWidget *norm_entry[3];
	GtkEntryBuffer *buffer_norm[3];
	t_gtkdata *entry_normx = NULL;
	t_gtkdata *entry_normy = NULL;
	t_gtkdata *entry_normz = NULL;

	entry_normx = malloc(sizeof(t_gtkdata));
	entry_normy = malloc(sizeof(t_gtkdata));
	entry_normz = malloc(sizeof(t_gtkdata));
	sprintf(s_entry,"%f", current_obj->norm.x);
	buffer_norm[0] = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%f", current_obj->norm.y);
	buffer_norm[1] = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%f", current_obj->norm.z);
	buffer_norm[2] = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	label = gtk_label_new("Normal");
	norm_entry[0] = gtk_entry_new_with_buffer(buffer_norm[0]);
	norm_entry[1] = gtk_entry_new_with_buffer(buffer_norm[1]);
	norm_entry[2] = gtk_entry_new_with_buffer(buffer_norm[2]);
	gtk_entry_set_width_chars ((GtkEntry *)norm_entry[0], 6);
	gtk_entry_set_width_chars ((GtkEntry *)norm_entry[1], 6);
	gtk_entry_set_width_chars ((GtkEntry *)norm_entry[2], 6);
	gtk_entry_set_max_length ((GtkEntry *)norm_entry[0], 6);
	gtk_entry_set_max_length ((GtkEntry *)norm_entry[1], 6);
	gtk_entry_set_max_length ((GtkEntry *)norm_entry[2], 6);
	gtk_grid_attach (GTK_GRID (grid), label, 0, 1, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), norm_entry[0], 1, 1, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), norm_entry[1], 2, 1, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), norm_entry[2], 3, 1, 1, 1);
	entry_normx->data = norm_entry[0];
	entry_normx->desc = ft_strdup("normx");
	entry_normx->obj = current_obj;
	entry_normy->data = norm_entry[1];
	entry_normy->desc = ft_strdup("normy");
	entry_normy->obj = current_obj;
	entry_normz->data = norm_entry[2];
	entry_normz->desc = ft_strdup("normz");
	entry_normz->obj = current_obj;
	g_signal_connect(norm_entry[0], "changed",
			G_CALLBACK(save_entry_transformation_object), entry_normx);
	g_signal_connect(norm_entry[1], "changed",
			G_CALLBACK(save_entry_transformation_object), entry_normy);
	g_signal_connect(norm_entry[2], "changed",
			G_CALLBACK(save_entry_transformation_object), entry_normz);
	g_signal_connect(norm_entry[0], "changed",
			G_CALLBACK(launch_preview), entry_normx);
	g_signal_connect(norm_entry[1], "changed",
			G_CALLBACK(launch_preview), entry_normy);
	g_signal_connect(norm_entry[2], "changed",
			G_CALLBACK(launch_preview), entry_normz);
}
