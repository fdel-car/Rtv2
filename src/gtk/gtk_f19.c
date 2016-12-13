#include "rt.h"

void	create_transformation_widget_light(void *object, GtkWidget *grid)
{
	GtkWidget *label[3];
	GtkWidget *pos_entry[3];
	GtkWidget *rayon_entry;
	GtkEntryBuffer *buffer_pos[3];
	GtkEntryBuffer *buffer_rayon;
	t_light *current_light;
	char *s_entry = NULL;
	t_gtkdata *entry_posx = NULL;
	t_gtkdata *entry_posy = NULL;
	t_gtkdata *entry_posz = NULL;
	t_gtkdata *entry_rayon = NULL;
	s_entry = malloc(sizeof(char) * 10);
	entry_posx = malloc(sizeof(t_gtkdata));
	entry_posy = malloc(sizeof(t_gtkdata));
	entry_posz = malloc(sizeof(t_gtkdata));
	entry_rayon = malloc(sizeof(t_gtkdata));
	current_light = (t_light *)object;
	sprintf(s_entry,"%f", current_light->pos.x);
	buffer_pos[0] = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%f", current_light->pos.y);
	buffer_pos[1] = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%f", current_light->pos.z);
	buffer_pos[2] = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%f", current_light->rayon);
	buffer_rayon = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	label[0] = gtk_label_new("    Position    ");
	label[2] = gtk_label_new("Rayon");
	pos_entry[0] = gtk_entry_new_with_buffer(buffer_pos[0]);
	pos_entry[1] = gtk_entry_new_with_buffer(buffer_pos[1]);
	pos_entry[2] = gtk_entry_new_with_buffer(buffer_pos[2]);
	rayon_entry = gtk_entry_new_with_buffer(buffer_rayon);
	direction_widget_light(current_light,grid,s_entry);
	gtk_entry_set_width_chars ((GtkEntry *)pos_entry[0], 6);
	gtk_entry_set_width_chars ((GtkEntry *)pos_entry[1], 6);
	gtk_entry_set_width_chars ((GtkEntry *)pos_entry[2], 6);
	gtk_entry_set_width_chars ((GtkEntry *)rayon_entry, 6);
	gtk_entry_set_max_length ((GtkEntry *)pos_entry[0], 6);
	gtk_entry_set_max_length ((GtkEntry *)pos_entry[1], 6);
	gtk_entry_set_max_length ((GtkEntry *)pos_entry[2], 6);
	gtk_entry_set_max_length ((GtkEntry *)rayon_entry, 6);
	gtk_grid_attach (GTK_GRID (grid), label[0], 0, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), label[2], 0, 2, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), pos_entry[0], 1, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), pos_entry[1], 2, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), pos_entry[2], 3, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), rayon_entry, 1, 2, 1, 1);
	entry_posx->data = pos_entry[0];
	entry_posx->desc = ft_strdup("posx");
	entry_posx->obj = current_light;
	entry_posy->data = pos_entry[1];
	entry_posy->desc = ft_strdup("posy");
	entry_posy->obj = current_light;
	entry_posz->data = pos_entry[2];
	entry_posz->desc = ft_strdup("posz");
	entry_posz->obj = current_light;
	entry_rayon->data = rayon_entry;
	entry_rayon->desc = ft_strdup("rayon");
	entry_rayon->obj = current_light;
	g_signal_connect(pos_entry[0], "changed",
			G_CALLBACK(save_entry_transformation_light), entry_posx);
	g_signal_connect(pos_entry[1], "changed",
			G_CALLBACK(save_entry_transformation_light), entry_posy);
	g_signal_connect(pos_entry[2], "changed",
			G_CALLBACK(save_entry_transformation_light), entry_posz);
	g_signal_connect(rayon_entry, "changed",
			G_CALLBACK(save_entry_transformation_light), entry_rayon);
	g_signal_connect(pos_entry[0], "changed",
			G_CALLBACK(launch_preview), entry_posx);
	g_signal_connect(pos_entry[1], "changed",
			G_CALLBACK(launch_preview), entry_posy);
	g_signal_connect(pos_entry[2], "changed",
			G_CALLBACK(launch_preview), entry_posz);
	g_signal_connect(rayon_entry, "changed",
			G_CALLBACK(launch_preview), entry_rayon);
}
