#include "rt.h"

void	direction_widget_light(t_light *current_obj, GtkWidget *grid,char *s_entry)
{
	GtkWidget *label;
	GtkWidget *dir_entry[3];
	GtkEntryBuffer *buffer_dir[3];
	t_gtkdata *entry_dirx = NULL;
	t_gtkdata *entry_diry = NULL;
	t_gtkdata *entry_dirz = NULL;
	entry_dirx = malloc(sizeof(t_gtkdata));
	entry_diry = malloc(sizeof(t_gtkdata));
	entry_dirz = malloc(sizeof(t_gtkdata));
	sprintf(s_entry,"%f", current_obj->dir.x);
	buffer_dir[0] = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%f", current_obj->dir.y);
	buffer_dir[1] = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%f", current_obj->dir.z);
	buffer_dir[2] = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	label = gtk_label_new("Direction");
	dir_entry[0] = gtk_entry_new_with_buffer(buffer_dir[0]);
	dir_entry[1] = gtk_entry_new_with_buffer(buffer_dir[1]);
	dir_entry[2] = gtk_entry_new_with_buffer(buffer_dir[2]);
	gtk_entry_set_width_chars ((GtkEntry *)dir_entry[0], 6);
	gtk_entry_set_width_chars ((GtkEntry *)dir_entry[1], 6);
	gtk_entry_set_width_chars ((GtkEntry *)dir_entry[2], 6);
	gtk_entry_set_max_length ((GtkEntry *)dir_entry[0], 6);
	gtk_entry_set_max_length ((GtkEntry *)dir_entry[1], 6);
	gtk_entry_set_max_length ((GtkEntry *)dir_entry[2], 6);
	gtk_grid_attach (GTK_GRID (grid), label, 0, 1, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), dir_entry[0], 1, 1, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), dir_entry[1], 2, 1, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), dir_entry[2], 3, 1, 1, 1);
	entry_dirx->data = dir_entry[0];
	entry_dirx->desc = ft_strdup("dirx");
	entry_dirx->obj = current_obj;
	entry_diry->data = dir_entry[1];
	entry_diry->desc = ft_strdup("diry");
	entry_diry->obj = current_obj;
	entry_dirz->data = dir_entry[2];
	entry_dirz->desc = ft_strdup("dirz");
	entry_dirz->obj = current_obj;
	g_signal_connect(dir_entry[0], "changed",
			G_CALLBACK(save_entry_transformation_light), entry_dirx);
	g_signal_connect(dir_entry[1], "changed",
			G_CALLBACK(save_entry_transformation_light), entry_diry);
	g_signal_connect(dir_entry[2], "changed",
			G_CALLBACK(save_entry_transformation_light), entry_dirz);
	g_signal_connect(dir_entry[0], "changed",
			G_CALLBACK(launch_preview), entry_dirx);
	g_signal_connect(dir_entry[1], "changed",
			G_CALLBACK(launch_preview), entry_diry);
	g_signal_connect(dir_entry[2], "changed",
			G_CALLBACK(launch_preview), entry_dirz);
}
