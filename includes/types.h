/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 15:44:03 by fdel-car          #+#    #+#             */
/*   Updated: 2016/10/24 15:44:08 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef enum {NONE, SPHERE, CYLINDER, CONE, PLANE} e_type;

typedef struct		s_vect
{
	float			x;
	float			y;
	float			z;
}					t_vect;

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct		s_cam
{
	t_vect			pos;
	t_vect			dir;
	t_vect			right;
	t_vect			up;
	t_vect			up_left;
	float			view_d;
	float			view_h;
	float			view_w;
	float			x_ind;
	float			y_ind;
}					t_cam;

typedef struct		s_mater
{
	float			shiny;
	float			int_refl;
	float			int_trans;
	t_color			color;
	char			*text;
}					t_mater;

typedef struct		s_data
{
	struct s_obj	*obj_hit;
	t_vect			hit_point;
	float			dist;
	float			solut;
	t_vect			dir;
	t_vect			orig;
	t_vect			norm;
	t_vect			light;
	t_vect			refl;
}					t_data;

typedef struct		s_obj
{
	short			type;
	char			*name;
	t_vect			pos;
	t_vect			dir;
	t_vect			norm;
	float			rayon;
	t_mater			mater;
	float			(*func)(struct s_obj *obj, t_data ray);
	void			*next;
}					t_obj;

typedef struct		s_light
{
	char			*name;
	gboolean		blur;
	t_vect			pos;
	t_color			color;
	float			rayon;
	float			intensity;
	char			*type;
	float			(*func)(t_obj *obj, t_data ray);
	void			*next;
}					t_light;

typedef struct		s_scene
{
	gboolean		gl_illum;
	int				iter_refl;
	char			*name;
	t_cam			cam;
	t_light			*lgt;
	t_obj			*obj;
}					t_scene;

typedef struct		s_env
{
	GdkPixbuf		*pix;
	GtkWidget		*win;
	GtkWidget		*img;
	GtkWidget		*box;
	GtkWidget		*list;
	guchar			*pixels;
	t_color			color;
	t_scene			scene;
	pthread_t		thread[NUM_THREAD];
	unsigned int	limits[NUM_THREAD];
	unsigned int	rowstride;
	unsigned char	id_thread;
}					t_env;

t_env g_env;

#endif