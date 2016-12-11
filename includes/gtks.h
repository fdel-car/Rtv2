/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtks.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 19:50:46 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/11 18:18:31 by fdel-car         ###   ########.fr       */
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

typedef struct	s_gtkdata
{
	GtkWidget	*data;
	void		*obj;
	char		*desc;
}				t_gtkdata;

void			left_filter(void);
void			right_filter(void);
void			create_list_of_objects();
void			set_signal_create_object(void);
void			set_signal_open_save_scene(void);
void			set_signal_switch_cam(void);
void			open_scene(void);
void			save_scene(void);
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

#endif
