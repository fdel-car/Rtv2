/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtks.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 19:50:46 by fdel-car          #+#    #+#             */
/*   Updated: 2016/11/06 19:50:47 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GTKS_H
# define GTKS_H

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct		s_gtkData
{
	GtkWidget		*data;
	void			*obj;
	char 			*desc;
}					t_gtkData;

void				create_list_of_objects();
void				select_current_obj(GtkTreeView *GtkTreeView,
					GtkTreePath *path);
void  set_signal_create_object(void);
void  set_signal_open_save_scene(void);
void  set_signal_switch_cam(void);
void open_scene(void);
void save_scene(void);
void switch_cam(GtkWidget *entry);
void create_object(GtkWidget *entry, t_gtkData *e);
void init_gtk_create_widget(void);

#endif
