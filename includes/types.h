/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 15:44:03 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/14 02:35:39 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct		s_gtkdata
{
	GtkWidget		*data;
	void			*obj;
	char			*desc;
}					t_gtkdata;

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

typedef struct		s_text
{
	int				tex_w;
	int				tex_h;
	int				size[2];
	unsigned char	buff[3];
	unsigned char	*text;
	float			tsize;
}					t_text;

typedef struct		s_noise
{
	float			gradtab[8][2];
	float			unit;
	float			tempx;
	float			tempy;
	float			s;
	float			t;
	float			u;
	float			v;
	float			cx;
	float			cy;
	float			li1;
	float			li2;
	float			tmp;
	int				x0;
	int				y0;
	int				ii;
	int				jj;
	int				gr0;
	int				gr1;
	int				gr2;
	int				gr3;
}					t_noise;

typedef struct		s_cam
{
	t_vect			pos;
	t_vect			pos1;
	t_vect			pos2;
	t_vect			pos3;
	t_vect			look_at;
	int				c_pos;
	t_vect			dir;
	t_vect			right;
	t_vect			up;
	t_vect			up_left;
	float			view_d;
	float			view_h;
	float			view_w;
	float			x_ind;
	float			y_ind;
	float			x_ind_p;
	float			y_ind_p;
	float			dist;
}					t_cam;

typedef struct		s_mater
{
	float			shiny;
	float			int_refl;
	float			int_trans;
	float			indice;
	t_color			color;
	t_text			*tex;
	t_text			*ntex;
	t_text			*ttex;
	t_text			*ctex;
}					t_mater;

typedef struct		s_data
{
	struct s_obj	*obj_hit;
	t_vect			hit_point;
	float			dist;
	float			solut;
	float			indice;
	t_vect			dir;
	t_vect			orig;
	t_vect			norm;
	t_vect			light;
	t_vect			refl;
	int				lights;
}					t_data;

typedef struct		s_obj
{
	t_vect			v0;
	t_vect			v1;
	t_vect			v2;
	t_vect			u;
	t_vect			v;
	char			*name;
	char			*src;
	t_vect			pos;
	t_vect			dir;
	t_vect			norm;
	t_vect			cut;
	t_vect			cut_pos;
	float			min;
	float			max;
	float			rayon;
	float			alpha;
	float			sphere_cut;
	t_mater			mater;
	float			(*func)(struct s_obj *obj, t_data ray);
	struct s_obj	*lst;
	void			*next;
	enum
	{
		NONE,
		SPHERE,
		CYLINDER,
		CONE,
		PLANE,
		TRIANGLE,
		MESH,
		SPOT_L,
		DIR_L,
		POINT_L,
		SKYBOX,
		OCULUS
	}				type;
}					t_obj;

typedef struct		s_light
{
	char			*name;
	gboolean		blur;
	t_vect			pos;
	t_vect			dir;
	t_color			color;
	float			rayon;
	float			alpha;
	float			intensity;
	float			(*func)(t_obj *obj, t_data ray);
	void			*next;
	enum
	{
		NONE,
		SPHERE,
		CYLINDER,
		CONE,
		PLANE,
		TRIANGLE,
		MESH,
		SPOT_L,
		DIR_L,
		POINT_L,
		SKYBOX,
		OCULUS
	}				type;
}					t_light;

typedef struct		s_scene
{
	float			ambiant;
	int				anti_alia;
	int				soft_shadow;
	int				iter_refl;
	int				iter_trans;
	char			*name;
	t_cam			cam;
	t_light			*lgt;
	t_obj			*obj;
}					t_scene;

typedef struct		s_norm
{
	GtkWidget		*mlabel[3];
	GtkWidget		*rayon_entry;
	GtkWidget		*norm_entry[3];
	GtkWidget		*dir_entry[3];
	GtkWidget		*label;
	GtkWidget		*pos_entry[3];
	GtkWidget		*shiny_label;
	GtkWidget		*refl_label;
	GtkWidget		*trans_label;
	GtkWidget		*color_label;
	GtkWidget		*text_label;
	GtkWidget		*indice_ref_label;
	GtkWidget		*shiny_entry;
	GtkWidget		*refl_entry;
	GtkWidget		*trans_entry;
	GtkWidget		*color_r_entry;
	GtkWidget		*color_g_entry;
	GtkWidget		*color_b_entry;
	GtkWidget		*text_entry;
	GtkWidget		*btn_text;
	GtkWidget		*ref_spin_button;
	GtkWidget		*intensity_label;
	GtkWidget		*blur_label;
	GtkWidget		*intensity_entry;
	GtkWidget		*blur_entry;
	GtkWidget		*color_button;
	GtkAdjustment	*adjustment;
	GtkEntryBuffer	*buffer_norm[3];
	GtkEntryBuffer	*buffer_dir[3];
	GtkEntryBuffer	*buffer_pos[3];
	GtkEntryBuffer	*buffer_rayon;
	GtkEntryBuffer	*intensity_buffer;
	GtkEntryBuffer	*blur_buffer;
	GtkEntryBuffer	*shiny_buffer;
	GtkEntryBuffer	*refl_buffer;
	GtkEntryBuffer	*trans_buffer;
	GtkEntryBuffer	*color_r_buffer;
	GtkEntryBuffer	*color_g_buffer;
	GtkEntryBuffer	*color_b_buffer;
	GtkEntryBuffer	*text_buffer;
	t_gtkdata		*entry_shiny;
	t_gtkdata		*entry_refl;
	t_gtkdata		*entry_trans;
	t_gtkdata		*entry_col_r;
	t_gtkdata		*entry_col_g;
	t_gtkdata		*entry_col_b;
	t_gtkdata		*entry_text;
	t_gtkdata		*entry_col;
	t_gtkdata		*entry_intensity;
	t_gtkdata		*entry_blur;
	t_gtkdata		*entry_posx;
	t_gtkdata		*entry_posy;
	t_gtkdata		*entry_posz;
	t_gtkdata		*entry_dirx;
	t_gtkdata		*entry_diry;
	t_gtkdata		*entry_dirz;
	t_gtkdata		*entry_normx;
	t_gtkdata		*entry_normy;
	t_gtkdata		*entry_normz;
	t_gtkdata		*entry_rayon;
}					t_norm;

typedef struct		s_env
{
	GtkBuilder		*build;
	GdkPixbuf		*pix;
	GdkPixbuf		*pix_prev;
	GdkPixbuf		*filter;
	GdkPixbuf		*stereoscopiqu;
	GtkWidget		*win;
	GtkWidget		*img;
	GtkWidget		*prev;
	GtkWidget		*toggle_prev;
	GtkWidget		*aa_choice;
	GtkWidget		*spin_refl;
	guchar			*pixels;
	guchar			*pixels_prev;
	guchar			*filter_p;
	guchar			*filter_r;
	guchar			*filter_gb;
	t_scene			scene;
	gboolean		state_prev;
	gboolean		stereo;
	gboolean		stereo_red;
	gboolean		oculus;
	gboolean		oculus_left;
	pthread_t		thread[NUM_THREAD];
	unsigned char	id_thread;
	unsigned int	limits[NUM_THREAD];
	unsigned int	limits_prev[NUM_THREAD];
	unsigned int	rowstride;
	unsigned int	rowstride_prev;
	unsigned int	progress;
	unsigned int	pixels_progress;
	unsigned int	total;
	unsigned int	progress_bar;
	int				width;
}					t_env;

t_env g_env;

#endif
