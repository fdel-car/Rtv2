/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_f12.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 12:20:52 by slgracie          #+#    #+#             */
/*   Updated: 2016/12/14 12:47:50 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	create_materw_object1(t_norm *me, t_obj *current_obj, char *s_entry)
{
	sprintf(s_entry, "%f", current_obj->mater.shiny);
	me->shiny_buffer = gtk_entry_buffer_new(s_entry, ft_strlen(s_entry));
	sprintf(s_entry, "%f", current_obj->mater.int_refl);
	me->refl_buffer = gtk_entry_buffer_new(s_entry, ft_strlen(s_entry));
	sprintf(s_entry, "%f", current_obj->mater.int_trans);
	me->trans_buffer = gtk_entry_buffer_new(s_entry, ft_strlen(s_entry));
	sprintf(s_entry, "%d", current_obj->mater.color.r);
	me->color_r_buffer = gtk_entry_buffer_new(s_entry, ft_strlen(s_entry));
	sprintf(s_entry, "%d", current_obj->mater.color.g);
	me->color_g_buffer = gtk_entry_buffer_new(s_entry, ft_strlen(s_entry));
	sprintf(s_entry, "%d", current_obj->mater.color.b);
	me->color_b_buffer = gtk_entry_buffer_new(s_entry, ft_strlen(s_entry));
	me->text_buffer = gtk_entry_buffer_new(s_entry, ft_strlen(s_entry));
	free(s_entry);
	me->shiny_label = gtk_label_new("Brillance");
	me->refl_label = gtk_label_new("Reflection");
	me->trans_label = gtk_label_new("Transparence");
	me->color_label = gtk_label_new("Color");
	me->text_label = gtk_label_new("Texture");
	me->indice_ref_label = gtk_label_new("indice Ref");
}

void	create_materw_object2(t_norm *me, t_obj *current_obj, GdkRGBA *col)
{
	me->shiny_entry = gtk_entry_new_with_buffer(me->shiny_buffer);
	me->refl_entry = gtk_entry_new_with_buffer(me->refl_buffer);
	me->trans_entry = gtk_entry_new_with_buffer(me->trans_buffer);
	me->color_r_entry = gtk_entry_new_with_buffer(me->color_r_buffer);
	me->color_g_entry = gtk_entry_new_with_buffer(me->color_g_buffer);
	me->color_b_entry = gtk_entry_new_with_buffer(me->color_b_buffer);
	me->text_entry = gtk_entry_new_with_buffer(me->text_buffer);
	me->btn_text = gtk_button_new_with_label("Tex");
	me->adjustment = gtk_adjustment_new(current_obj->mater.indice,
	0.9, 1.1, 0.01, 0.1, 0.0);
	me->ref_spin_button = gtk_spin_button_new(me->adjustment, 0.01, 3);
	col->red = (double)current_obj->mater.color.r / 255;
	col->green = (double)current_obj->mater.color.g / 255;
	col->blue = (double)current_obj->mater.color.b / 255;
	col->alpha = 1;
	me->color_button = gtk_color_button_new_with_rgba((const GdkRGBA *)col);
	me->entry_col->data = me->color_button;
	me->entry_col->desc = ft_strdup("color");
	me->entry_col->obj = current_obj;
	gtk_entry_set_width_chars((GtkEntry *)me->shiny_entry, 6);
	gtk_entry_set_width_chars((GtkEntry *)me->refl_entry, 6);
	gtk_entry_set_width_chars((GtkEntry *)me->trans_entry, 6);
	gtk_entry_set_width_chars((GtkEntry *)me->color_r_entry, 3);
	gtk_entry_set_width_chars((GtkEntry *)me->color_g_entry, 3);
}

void	create_materw_object3(t_norm *me, GtkWidget *grid)
{
	gtk_entry_set_width_chars((GtkEntry *)me->color_b_entry, 3);
	gtk_entry_set_width_chars((GtkEntry *)me->text_entry, 6);
	gtk_entry_set_max_length((GtkEntry *)me->shiny_entry, 6);
	gtk_entry_set_max_length((GtkEntry *)me->refl_entry, 6);
	gtk_entry_set_max_length((GtkEntry *)me->trans_entry, 6);
	gtk_entry_set_max_length((GtkEntry *)me->color_r_entry, 3);
	gtk_entry_set_max_length((GtkEntry *)me->color_g_entry, 3);
	gtk_entry_set_max_length((GtkEntry *)me->color_b_entry, 3);
	gtk_entry_set_max_length((GtkEntry *)me->text_entry, 6);
	gtk_grid_attach(GTK_GRID(grid), me->shiny_label, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->refl_label, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->trans_label, 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->color_label, 0, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->text_label, 0, 4, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->indice_ref_label, 0, 5, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->shiny_entry, 1, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->refl_entry, 1, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->trans_entry, 1, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->color_r_entry, 1, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->color_g_entry, 2, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->color_b_entry, 3, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->color_button, 4, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), me->btn_text, 1, 4, 4, 1);
	gtk_grid_attach(GTK_GRID(grid), me->ref_spin_button, 1, 5, 4, 1);
}

void	create_materw_object4(t_norm *me, t_obj *current_obj)
{
	me->entry_shiny->data = me->shiny_entry;
	me->entry_shiny->desc = ft_strdup("shiny");
	me->entry_shiny->obj = current_obj;
	me->entry_refl->data = me->refl_entry;
	me->entry_refl->desc = ft_strdup("refl");
	me->entry_refl->obj = current_obj;
	me->entry_trans->data = me->trans_entry;
	me->entry_trans->desc = ft_strdup("trans");
	me->entry_trans->obj = current_obj;
	me->entry_col_r->data = me->color_r_entry;
	me->entry_col_r->desc = ft_strdup("colr");
	me->entry_col_r->obj = current_obj;
	me->entry_col_g->data = me->color_g_entry;
	me->entry_col_g->desc = ft_strdup("colg");
	me->entry_col_g->obj = current_obj;
	me->entry_col_b->data = me->color_b_entry;
	me->entry_col_b->desc = ft_strdup("colb");
	me->entry_col_b->obj = current_obj;
	me->entry_text->data = me->text_entry;
	me->entry_text->desc = ft_strdup("text");
	me->entry_text->obj = current_obj;
	g_signal_connect(me->shiny_entry, "changed",
			G_CALLBACK(save_entry_material_object), me->entry_shiny);
}

void	create_material_widget_object(void *object, GtkWidget *grid)
{
	t_norm		me;
	t_obj		*current_obj;
	char		*s_entry;
	GdkRGBA		*col;

	col = malloc(sizeof(GdkRGBA));
	s_entry = malloc(sizeof(char) * 10);
	me.entry_shiny = malloc(sizeof(t_gtkdata));
	me.entry_refl = malloc(sizeof(t_gtkdata));
	me.entry_trans = malloc(sizeof(t_gtkdata));
	me.entry_col_r = malloc(sizeof(t_gtkdata));
	me.entry_col_g = malloc(sizeof(t_gtkdata));
	me.entry_col_b = malloc(sizeof(t_gtkdata));
	me.entry_text = malloc(sizeof(t_gtkdata));
	me.entry_col = malloc(sizeof(t_gtkdata));
	current_obj = (t_obj *)object;
	create_materw_object1(&me, current_obj, s_entry);
	create_materw_object2(&me, current_obj, col);
	create_materw_object3(&me, grid);
	create_materw_object4(&me, current_obj);
	create_materw_object5(&me);
	create_materw_object6(&me);
}
