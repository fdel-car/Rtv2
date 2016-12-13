#include "rt.h"

void	position_widget(t_obj *current_obj, GtkWidget *grid,char *s_entry)
{
	GtkWidget *label;
	GtkWidget *pos_entry[3];
	GtkEntryBuffer *buffer_pos[3];
	t_gtkdata *entry_posx = NULL;
	t_gtkdata *entry_posy = NULL;
	t_gtkdata *entry_posz = NULL;

	entry_posx = malloc(sizeof(t_gtkdata));
	entry_posy = malloc(sizeof(t_gtkdata));
	entry_posz = malloc(sizeof(t_gtkdata));
	sprintf(s_entry,"%f", current_obj->pos.x);
	buffer_pos[0] = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%f", current_obj->pos.y);
	buffer_pos[1] = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%f", current_obj->pos.z);
	buffer_pos[2] = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	label = gtk_label_new("    Position     ");
	pos_entry[0] = gtk_entry_new_with_buffer(buffer_pos[0]);
	pos_entry[1] = gtk_entry_new_with_buffer(buffer_pos[1]);
	pos_entry[2] = gtk_entry_new_with_buffer(buffer_pos[2]);
	gtk_entry_set_width_chars ((GtkEntry *)pos_entry[0], 6);
	gtk_entry_set_width_chars ((GtkEntry *)pos_entry[1], 6);
	gtk_entry_set_width_chars ((GtkEntry *)pos_entry[2], 6);
	gtk_entry_set_max_length ((GtkEntry *)pos_entry[0], 6);
	gtk_entry_set_max_length ((GtkEntry *)pos_entry[1], 6);
	gtk_entry_set_max_length ((GtkEntry *)pos_entry[2], 6);
	gtk_grid_attach (GTK_GRID (grid), label, 0, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), pos_entry[0], 1, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), pos_entry[1], 2, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), pos_entry[2], 3, 0, 1, 1);
	entry_posx->data = pos_entry[0];
	entry_posx->desc = ft_strdup("posx");
	entry_posx->obj = current_obj;
	entry_posy->data = pos_entry[1];
	entry_posy->desc = ft_strdup("posy");
	entry_posy->obj = current_obj;
	entry_posz->data = pos_entry[2];
	entry_posz->desc = ft_strdup("posz");
	entry_posz->obj = current_obj;
	g_signal_connect(pos_entry[0], "changed",
			G_CALLBACK(save_entry_transformation_object), entry_posx);
	g_signal_connect(pos_entry[1], "changed",
			G_CALLBACK(save_entry_transformation_object), entry_posy);
	g_signal_connect(pos_entry[2], "changed",
			G_CALLBACK(save_entry_transformation_object), entry_posz);
	g_signal_connect(pos_entry[0], "changed",
			G_CALLBACK(launch_preview), entry_posx);
	g_signal_connect(pos_entry[1], "changed",
			G_CALLBACK(launch_preview), entry_posy);
	g_signal_connect(pos_entry[2], "changed",
			G_CALLBACK(launch_preview), entry_posz);
}
