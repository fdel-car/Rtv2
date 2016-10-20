/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 18:45:50 by fdel-car          #+#    #+#             */
/*   Updated: 2016/09/05 18:49:48 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# define WIDTH 1920
# define HEIGHT 1080
# define SQ(x) ((x) * (x))

# include <stdlib.h>
# include <gtk/gtk.h>
# include <stdlib.h>
# include <math.h>
# include "libft.h"

typedef struct		s_vect
{
	float			x;
	float			y;
	float			z;
}					t_vect;

typedef struct		s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_color;

typedef struct		s_cam
{
	t_vect			pos;
	t_vect			dir;
}					t_cam;

typedef struct		s_lights
{
	gboolean		blur;
	t_vect			pos;
	t_color			color;
	float			rayon;
	float			intensity;
	char			*type;
	void			*func;
}					t_lights;

typedef struct		s_mater
{
	gboolean		shiny;
	float			int_refl;
	float			int_trans;
	t_color			color;
	char			*text;
	void			*func;
}					t_mater;

typedef struct		s_obj
{
	char			*name;
	t_vect			pos;
	t_vect			dir;
	t_vect			norm;
	float			rayon;
	t_mater			mater;
	void			*next;
}					t_obj;

typedef struct		s_scene
{
	gboolean		gl_illum;
	int				iter_refl;
	char			*name;
	t_cam			cam;
	t_lights		*lst_lght;
	t_obj			*lst_obj;
}					t_scene;

typedef struct		s_env
{
	GdkPixbuf		*pix;
	GtkAdjustment	*red_adjust;
	GtkAdjustment	*green_adjust;
	GtkAdjustment	*blue_adjust;
	GtkWidget		*win;
	GtkWidget		*img;
	GtkWidget		*box;
	GtkWidget		*box_red;
	GtkWidget		*box_green;
	GtkWidget		*box_blue;
	GtkWidget		*list;
	GtkWidget		*red_scale;
	GtkWidget		*green_scale;
	GtkWidget		*blue_scale;
	GtkWidget		*button;
	GMainLoop		*loop;
	guchar			*pixels;
	gint			rowstride;
	t_color			color;
	t_scene			scene;
}					t_env;

t_env g_env;

#endif
