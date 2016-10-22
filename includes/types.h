#ifndef TYPES_H
# define TYPES_H

typedef struct	s_vect
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

typedef struct		s_light
{
  char        *name;
	gboolean		blur;
	t_vect			pos;
	t_color			color;
	float			rayon;
	float			intensity;
	char			*type;
	void			*func;
	void			*next;
}					t_light;

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
	short			type;
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
	t_light	*lgt;
	t_obj			*obj;
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
