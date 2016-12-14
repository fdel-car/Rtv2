/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtks.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 19:50:46 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/14 12:51:16 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GTKS_H
# define GTKS_H

# define ANSI_COLOR_RED "\x1b[31m"
# define ANSI_COLOR_GREEN "\x1b[32m"
# define ANSI_COLOR_YELLOW "\x1b[33m"
# define ANSI_COLOR_BLUE "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN "\x1b[36m"
# define ANSI_COLOR_RESET "\x1b[0m"
# define DIST_INTEROCULAR 0.55

void			hide_window(void);
void			open_file(char *filename);
void			switch_cam_pos();
void			save_image_chooser(void);
void			switch_cam(GtkWidget *entry);
void			open_scene();
void			check_filter();
void			init_limits(void);
void			switch_filter(GtkWidget *combo);
void			init_gtk_filter_widget(void);
void			init_gtk_create_widget(void);
void			clear_entry_1(void);
void			clear_entry_2(void);
void			clear_entry_3(void);
void			clear_entry_4(void);
void			clear_entry_widget_add_object(void);
void			hide_window();
void			signal_add_object(void);
void			delete_objects(void *obj, unsigned int n);
void			*find_objects(char *name, unsigned int *n);
void			create_object(GtkWidget *entry, t_gtkdata *e);
void			save_color_material_light(GtkEntry *entry, t_gtkdata *data);
void			save_color_material(GtkEntry *entry, t_gtkdata *data);
void			save_indice_ref(GtkSpinButton *btn, t_gtkdata *data);
void			save_entry_transformation_light(GtkEntry *entry,
				t_gtkdata *data);
void			save_translation_mesh_object(GtkEntry *entry, t_gtkdata *data,
				t_vect oldpos);
void			save_entry_transformation_object(GtkEntry *entry,
				t_gtkdata *data);
void			save_entry_material_object(GtkEntry *entry, t_gtkdata *data);
void			select_text(GtkEntry *entry, t_gtkdata *data);
void			save_entry_material_light(GtkEntry *entry, t_gtkdata *data);
void			create_material_widget_object(void *object, GtkWidget *grid);
void			create_material_widget_light(void *object, GtkWidget *grid);
void			position_widget(t_obj *current_obj, GtkWidget *grid,
				char *s_entry);
void			direction_widget(t_obj *current_obj, GtkWidget *grid,
				char *s_entry);
void			normal_widget(t_obj *current_obj, GtkWidget *grid,
				char *s_entry);
void			rayon_widget(t_obj *current_obj, GtkWidget *grid,
				char *s_entry);
void			alpha_widget(t_obj *current_obj, GtkWidget *grid,
				char *s_entry);
void			create_transformation_widget_object(void *object,
				GtkWidget *grid);
void			direction_widget_light(t_light *current_obj, GtkWidget *grid,
				char *s_entry);
void			create_transformation_widget_light(void *object,
				GtkWidget *grid);
void			create_list_of_attributs(void *objects, unsigned int type);
void			select_current_obj(GtkTreeView *treeview, GtkTreePath *path);
void			view_popup_menu_delete_row(GtkWidget *menuitem,
				gpointer userdata);
void			view_popup_menu(GtkWidget *treeview, GdkEventButton *event,
				GtkTreePath *path, gpointer userdata);
void			create_list_of_objects(void);
t_obj			*add_object_type(char *s, t_obj *obj);
t_obj			*add_object_name(t_obj *obj);
t_obj			*add_object_pos(t_obj *obj);
t_obj			*add_object_dir(t_obj *obj);
t_obj			*add_object_norm(t_obj *obj);
t_obj			*add_object_rayon(t_obj *obj);
t_obj			*add_object_alpha(t_obj *obj);
t_obj			*add_object_mater_shiny(t_obj *obj);
t_obj			*add_object_mater_refl(t_obj *obj);
t_obj			*add_object_mater_trans(t_obj *obj);
t_obj			*add_object_mater_color(t_obj *obj);
void			left_filter(void);
void			right_filter(void);
void			create_list_of_objects();
void			set_signal_create_object(void);
void			set_signal_open_save_scene(void);
void			set_signal_switch_cam(void);
void			open_scene(void);
void			switch_cam(GtkWidget *entry);
void			create_object(GtkWidget *entry, t_gtkdata *e);
void			select_current_obj(GtkTreeView *treeview, GtkTreePath *path);
void			init_gtk_create_widget(void);
void			init_gtk_filter_widget(void);
void			save_img(char *filename);
void			save_image_chooser(void);
void			check_filter(void);
void			stereoscopique_filter(void);
void			red_filter();
void			green_blue_filter();
void			add_cylindre_adn(t_obj *o, t_vect pos, t_vect pos1);
void			add_adn(t_obj *o);
void			add_sphere_adn(t_obj *o, t_vect pos);
void			hide_window(void);
gboolean		view_onbuttonpressed(GtkWidget *treeview, GdkEventButton *event,
				gpointer userdata);
void			create_materw_object5(t_norm *me);
void			create_materw_object6(t_norm *me);
#endif
