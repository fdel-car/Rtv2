#include "rt.h"

void	create_material_widget_object(void *object, GtkWidget *grid)
{
	GtkWidget *shiny_label;
	GtkWidget *refl_label;
	GtkWidget *trans_label;
	GtkWidget *color_label;
	GtkWidget *text_label;
	GtkWidget *indice_ref_label;
	GtkWidget *shiny_entry;
	GtkWidget *refl_entry;
	GtkWidget *trans_entry;
	GtkWidget *color_r_entry;
	GtkWidget *color_g_entry;
	GtkWidget *color_b_entry;
	GtkWidget *text_entry;
	GtkWidget *btn_text;
	GtkWidget *color_button;
	GtkWidget *ref_spin_button;
	GtkAdjustment *adjustment;
	GtkEntryBuffer *shiny_buffer;
	GtkEntryBuffer *refl_buffer;
	GtkEntryBuffer *trans_buffer;
	GtkEntryBuffer *color_r_buffer;
	GtkEntryBuffer *color_g_buffer;
	GtkEntryBuffer *color_b_buffer;
	GtkEntryBuffer *text_buffer;
	t_obj *current_obj;
	char *s_entry = NULL;
	t_gtkdata *entry_shiny = NULL;
	t_gtkdata *entry_refl = NULL;
	t_gtkdata *entry_trans = NULL;
	t_gtkdata *entry_col_r = NULL;
	t_gtkdata *entry_col_g = NULL;
	t_gtkdata *entry_col_b = NULL;
	t_gtkdata *entry_text = NULL;
	t_gtkdata *entry_col = NULL;
	GdkRGBA *col = malloc(sizeof(GdkRGBA));

	s_entry = malloc(sizeof(char) * 10);
	entry_shiny = malloc(sizeof(t_gtkdata));
	entry_refl = malloc(sizeof(t_gtkdata));
	entry_trans = malloc(sizeof(t_gtkdata));
	entry_col_r= malloc(sizeof(t_gtkdata));
	entry_col_g = malloc(sizeof(t_gtkdata));
	entry_col_b = malloc(sizeof(t_gtkdata));
	entry_text = malloc(sizeof(t_gtkdata));
	entry_col = malloc(sizeof(t_gtkdata));
	current_obj = (t_obj *)object;
	sprintf(s_entry,"%f", current_obj->mater.shiny);
	shiny_buffer = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%f", current_obj->mater.int_refl);
	refl_buffer = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%f", current_obj->mater.int_trans);
	trans_buffer = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%d", current_obj->mater.color.r);
	color_r_buffer = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%d", current_obj->mater.color.g);
	color_g_buffer = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%d", current_obj->mater.color.b);
	color_b_buffer = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	// sprintf(s_entry,"%s", current_obj->mater.text);
	text_buffer = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	free(s_entry);
	shiny_label = gtk_label_new("Brillance");
	refl_label = gtk_label_new("Reflection");
	trans_label = gtk_label_new("Transparence");
	color_label = gtk_label_new("Color");
	text_label = gtk_label_new("Texture");
	indice_ref_label = gtk_label_new("indice Ref");
	shiny_entry = gtk_entry_new_with_buffer(shiny_buffer);
	refl_entry = gtk_entry_new_with_buffer(refl_buffer);
	trans_entry = gtk_entry_new_with_buffer(trans_buffer);
	color_r_entry = gtk_entry_new_with_buffer(color_r_buffer);
	color_g_entry = gtk_entry_new_with_buffer(color_g_buffer);
	color_b_entry = gtk_entry_new_with_buffer(color_b_buffer);
	text_entry = gtk_entry_new_with_buffer(text_buffer);
	btn_text = gtk_button_new_with_label ("Tex");
	adjustment = gtk_adjustment_new (current_obj->mater.indice, 0.9, 1.1, 0.01, 0.1, 0.0);
	ref_spin_button = gtk_spin_button_new (adjustment, 0.01, 3);
	col->red  = (double)current_obj->mater.color.r / 255;
	col->green  = (double)current_obj->mater.color.g / 255;
	col->blue  = (double)current_obj->mater.color.b / 255;
	col->alpha = 1;
	color_button = gtk_color_button_new_with_rgba ((const GdkRGBA *)col);
	entry_col->data = color_button;
	entry_col->desc = ft_strdup("color");
	entry_col->obj = current_obj;
	gtk_entry_set_width_chars ((GtkEntry *)shiny_entry, 6);
	gtk_entry_set_width_chars ((GtkEntry *)refl_entry, 6);
	gtk_entry_set_width_chars ((GtkEntry *)trans_entry, 6);
	gtk_entry_set_width_chars ((GtkEntry *)color_r_entry, 3);
	gtk_entry_set_width_chars ((GtkEntry *)color_g_entry, 3);
	gtk_entry_set_width_chars ((GtkEntry *)color_b_entry, 3);
	gtk_entry_set_width_chars ((GtkEntry *)text_entry, 6);
	gtk_entry_set_max_length ((GtkEntry *)shiny_entry, 6);
	gtk_entry_set_max_length ((GtkEntry *)refl_entry, 6);
	gtk_entry_set_max_length ((GtkEntry *)trans_entry, 6);
	gtk_entry_set_max_length ((GtkEntry *)color_r_entry, 3);
	gtk_entry_set_max_length ((GtkEntry *)color_g_entry, 3);
	gtk_entry_set_max_length ((GtkEntry *)color_b_entry, 3);
	gtk_entry_set_max_length ((GtkEntry *)text_entry, 6);
	gtk_grid_attach(GTK_GRID(grid), shiny_label,0,0,1,1);
	gtk_grid_attach(GTK_GRID(grid), refl_label,0,1,1,1);
	gtk_grid_attach(GTK_GRID(grid), trans_label,0,2,1,1);
	gtk_grid_attach(GTK_GRID(grid), color_label,0,3,1,1);
	gtk_grid_attach(GTK_GRID(grid), text_label,0,4,1,1);
	gtk_grid_attach(GTK_GRID(grid), indice_ref_label,0,5,1,1);
	gtk_grid_attach(GTK_GRID(grid), shiny_entry,1,0,1,1);
	gtk_grid_attach(GTK_GRID(grid), refl_entry,1,1,1,1);
	gtk_grid_attach(GTK_GRID(grid), trans_entry,1,2,1,1);
	gtk_grid_attach(GTK_GRID(grid), color_r_entry,1,3,1,1);
	gtk_grid_attach(GTK_GRID(grid), color_g_entry,2,3,1,1);
	gtk_grid_attach(GTK_GRID(grid), color_b_entry,3,3,1,1);
	gtk_grid_attach(GTK_GRID(grid), color_button,4,3,1,1);
	//	gtk_grid_attach(GTK_GRID(grid), text_entry,1,4,1,1);
	gtk_grid_attach(GTK_GRID(grid), btn_text,1,4,4,1);
	gtk_grid_attach(GTK_GRID(grid), ref_spin_button,1,5,4,1);
	entry_shiny->data = shiny_entry;
	entry_shiny->desc = ft_strdup("shiny");
	entry_shiny->obj = current_obj;
	entry_refl->data = refl_entry;
	entry_refl->desc = ft_strdup("refl");
	entry_refl->obj = current_obj;
	entry_trans->data = trans_entry;
	entry_trans->desc = ft_strdup("trans");
	entry_trans->obj = current_obj;
	entry_col_r->data = color_r_entry;
	entry_col_r->desc = ft_strdup("colr");
	entry_col_r->obj = current_obj;
	entry_col_g->data = color_g_entry;
	entry_col_g->desc = ft_strdup("colg");
	entry_col_g->obj = current_obj;
	entry_col_b->data = color_b_entry;
	entry_col_b->desc = ft_strdup("colb");
	entry_col_b->obj = current_obj;
	entry_text->data = text_entry;
	entry_text->desc = ft_strdup("text");
	entry_text->obj = current_obj;
	g_signal_connect(shiny_entry, "changed",
			G_CALLBACK(save_entry_material_object), entry_shiny);
	g_signal_connect(refl_entry, "changed",
			G_CALLBACK(save_entry_material_object), entry_refl);
	g_signal_connect(trans_entry, "changed",
			G_CALLBACK(save_entry_material_object), entry_trans);
	g_signal_connect(color_r_entry, "changed",
			G_CALLBACK(save_entry_material_object), entry_col_r);
	g_signal_connect(color_g_entry, "changed",
			G_CALLBACK(save_entry_material_object), entry_col_g);
	g_signal_connect(color_b_entry, "changed",
			G_CALLBACK(save_entry_material_object), entry_col_b);
	g_signal_connect(text_entry, "changed",
			G_CALLBACK(save_entry_material_object), entry_text);
	g_signal_connect(btn_text, "clicked",
			G_CALLBACK(select_text), entry_text);
	g_signal_connect(ref_spin_button, "value-changed",
			G_CALLBACK(save_indice_ref), entry_text);
	g_signal_connect(shiny_entry, "changed",
			G_CALLBACK(launch_preview), entry_shiny);
	g_signal_connect(refl_entry, "changed",
			G_CALLBACK(launch_preview), entry_refl);
	g_signal_connect(trans_entry, "changed",
			G_CALLBACK(launch_preview), entry_trans);
	g_signal_connect(color_r_entry, "changed",
			G_CALLBACK(launch_preview), entry_col_r);
	g_signal_connect(color_g_entry, "changed",
			G_CALLBACK(launch_preview), entry_col_g);
	g_signal_connect(color_b_entry, "changed",
			G_CALLBACK(launch_preview), entry_col_b);
	g_signal_connect(text_entry, "changed",
			G_CALLBACK(launch_preview), entry_text);
	g_signal_connect(color_button, "color-set",
			G_CALLBACK(save_color_material), entry_col);
	g_signal_connect(color_button, "color-set",
			G_CALLBACK(launch_preview), entry_col);
}
