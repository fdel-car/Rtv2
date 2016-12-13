#include "rt.h"

void	create_material_widget_light(void *object, GtkWidget *grid)
{
	GtkWidget *intensity_label;
	GtkWidget *blur_label;
	GtkWidget *color_label;
	GtkWidget *intensity_entry;
	GtkWidget *blur_entry;
	GtkWidget *color_r_entry;
	GtkWidget *color_g_entry;
	GtkWidget *color_b_entry;
	GtkWidget *color_button;
	GtkEntryBuffer *intensity_buffer;
	GtkEntryBuffer *blur_buffer;
	GtkEntryBuffer *color_r_buffer;
	GtkEntryBuffer *color_g_buffer;
	GtkEntryBuffer *color_b_buffer;
	t_light *current_obj;
	char *s_entry = NULL;
	t_gtkdata *entry_intensity = NULL;
	t_gtkdata *entry_blur = NULL;
	t_gtkdata *entry_col_r = NULL;
	t_gtkdata *entry_col_g = NULL;
	t_gtkdata *entry_col_b = NULL;
	t_gtkdata *entry_col = NULL;
	GdkRGBA *col = malloc(sizeof(GdkRGBA));

	s_entry = malloc(sizeof(char) * 10);
	entry_intensity = malloc(sizeof(t_gtkdata));
	entry_blur = malloc(sizeof(t_gtkdata));
	entry_col_r= malloc(sizeof(t_gtkdata));
	entry_col_g = malloc(sizeof(t_gtkdata));
	entry_col_b = malloc(sizeof(t_gtkdata));
	entry_col = malloc(sizeof(t_gtkdata));
	current_obj = (t_light *)object;
	sprintf(s_entry,"%f", current_obj->intensity);
	intensity_buffer = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%d", current_obj->blur);
	blur_buffer = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%d", current_obj->color.r);
	color_r_buffer = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%d", current_obj->color.g);
	color_g_buffer = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%d", current_obj->color.b);
	color_b_buffer = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	free(s_entry);
	intensity_label = gtk_label_new("    Intensite    ");
	blur_label = gtk_label_new("Blur");
	color_label = gtk_label_new("Color");
	intensity_entry = gtk_entry_new_with_buffer(intensity_buffer);
	blur_entry = gtk_entry_new_with_buffer(blur_buffer);
	color_r_entry = gtk_entry_new_with_buffer(color_r_buffer);
	color_g_entry = gtk_entry_new_with_buffer(color_g_buffer);
	color_b_entry = gtk_entry_new_with_buffer(color_b_buffer);
	col->red  = (double)current_obj->color.r / 255;
	col->green  = (double)current_obj->color.g / 255;
	col->blue  = (double)current_obj->color.b / 255;
	col->alpha = 1;
	color_button = gtk_color_button_new_with_rgba ((const GdkRGBA *)col);
	entry_col->data = color_button;
	entry_col->desc = ft_strdup("color");
	entry_col->obj = current_obj;
	gtk_entry_set_width_chars ((GtkEntry *)intensity_entry, 6);
	gtk_entry_set_width_chars ((GtkEntry *)blur_entry, 6);
	gtk_entry_set_width_chars ((GtkEntry *)color_r_entry, 3);
	gtk_entry_set_width_chars ((GtkEntry *)color_g_entry, 3);
	gtk_entry_set_width_chars ((GtkEntry *)color_b_entry, 3);
	gtk_entry_set_max_length ((GtkEntry *)intensity_entry, 6);
	gtk_entry_set_max_length ((GtkEntry *)blur_entry, 6);
	gtk_entry_set_max_length ((GtkEntry *)color_r_entry, 3);
	gtk_entry_set_max_length ((GtkEntry *)color_g_entry, 3);
	gtk_entry_set_max_length ((GtkEntry *)color_b_entry, 3);
	gtk_grid_attach(GTK_GRID(grid), intensity_label,0,0,1,1);
	gtk_grid_attach(GTK_GRID(grid), blur_label,0,1,1,1);
	gtk_grid_attach(GTK_GRID(grid), color_label,0,2,1,1);
	gtk_grid_attach(GTK_GRID(grid), intensity_entry,1,0,1,1);
	gtk_grid_attach(GTK_GRID(grid), blur_entry,1,1,1,1);
	gtk_grid_attach(GTK_GRID(grid), color_r_entry,1,2,1,1);
	gtk_grid_attach(GTK_GRID(grid), color_g_entry,2,2,1,1);
	gtk_grid_attach(GTK_GRID(grid), color_b_entry,3,2,1,1);
	gtk_grid_attach(GTK_GRID(grid), color_button,4,2,1,1);
	entry_intensity->data = intensity_entry;
	entry_intensity->desc = ft_strdup("intens");
	entry_intensity->obj = current_obj;
	entry_blur->data = blur_entry;
	entry_blur->desc = ft_strdup("blur");
	entry_blur->obj = current_obj;
	entry_col_r->data = color_r_entry;
	entry_col_r->desc = ft_strdup("colr");
	entry_col_r->obj = current_obj;
	entry_col_g->data = color_g_entry;
	entry_col_g->desc = ft_strdup("colg");
	entry_col_g->obj = current_obj;
	entry_col_b->data = color_b_entry;
	entry_col_b->desc = ft_strdup("colb");
	entry_col_b->obj = current_obj;
	g_signal_connect(intensity_entry, "changed",
			G_CALLBACK(save_entry_material_light), entry_intensity);
	g_signal_connect(blur_entry, "changed",
			G_CALLBACK(save_entry_material_light), entry_blur);
	g_signal_connect(color_r_entry, "changed",
			G_CALLBACK(save_entry_material_light), entry_col_r);
	g_signal_connect(color_g_entry, "changed",
			G_CALLBACK(save_entry_material_light), entry_col_g);
	g_signal_connect(color_b_entry, "changed",
			G_CALLBACK(save_entry_material_light), entry_col_b);
	g_signal_connect(intensity_entry, "changed",
			G_CALLBACK(launch_preview), entry_intensity);
	g_signal_connect(blur_entry, "changed",
			G_CALLBACK(launch_preview), entry_blur);
	g_signal_connect(color_r_entry, "changed",
			G_CALLBACK(launch_preview), entry_col_r);
	g_signal_connect(color_g_entry, "changed",
			G_CALLBACK(launch_preview), entry_col_g);
	g_signal_connect(color_b_entry, "changed",
			G_CALLBACK(launch_preview), entry_col_b);
	g_signal_connect(color_button, "color-set",
			G_CALLBACK(save_color_material_light), entry_col);
	g_signal_connect(color_button, "color-set",
			G_CALLBACK(launch_preview), entry_col);
}
