/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 15:43:09 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/13 19:57:16 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACING_H
# define RAYTRACING_H
# define EPSILON 0.001

int			vec_is_null(t_vect u);
int			g_pos(guchar *new, int x, int y);
float		sphere_cut(float *r, t_data ray, t_vect cut_pos, t_vect cut);
float		texture_cut(float res, t_obj *o, t_data mray);
float		texture_cutr(float res, float *r, t_obj *o, t_data mray);
float		cut_basics(t_data *ray, t_obj *o, t_vect cut, float *r);
float		quadratic_root(float a, float b, float c, float *roots);
float		vec_dotp(t_vect u, t_vect v);
float		dist_p(t_vect u, t_vect v);
float		get_shadow(t_light *l, t_data *ray);
float		intersect_triangle(t_obj *obj, t_data ray);
float		intersect_sphere(t_obj *obj, t_data ray);
float		intersect_cylinder(t_obj *obj, t_data ray);
float		intersect_cone(t_obj *obj, t_data ray);
float		intersect_plane(t_obj *obj, t_data ray);
t_data		oculus_view(t_data ray);
t_data		intersect_obj(t_data ray, gboolean sh, gboolean prev);
t_color		compute_light(t_data ray, int iter_refl, int iter_trans);
t_color		get_texture(t_data ray, t_text *tex);
t_color		getex_sphere(t_data ray, t_text *tex);
t_color		getex_cyl(t_data ray, t_text *tex);
t_color		getex_plane(t_data ray, t_text *tex);
t_color		greyscale(t_color c);
t_color		get_color_img(guchar *new, int *xy, int i, int j);
t_color		transparent_lighting(t_data *ray, int iter_refl, int iter_trans,
			t_color c);
t_color		specular_lighting(t_data *ray, t_light *l);
t_color		render_ray(t_data ray);
t_vect		bump_normal(t_color	p);
t_vect		refract_dir_bis(t_data *ray, t_obj *obj, float n, float cos);
t_vect		vec_new(float x, float y, float z);
t_vect		cross_pr(t_vect u, t_vect v);
t_vect		vec_mult(t_vect u, float value);
t_vect		vec_mul(t_vect u, t_vect v);
t_vect		vec_sub(t_vect u, t_vect v);
t_vect		vec_add(t_vect u, t_vect v);
t_vect		vec_norm(t_vect u);
t_vect		rot_x(float theta, t_vect u);
t_vect		rot_y(float theta, t_vect u);
t_vect		rot_z(float theta, t_vect u);
t_vect		rot_any(t_vect u, t_vect a, float theta);
gboolean	key_event(GtkWidget *win, GdkEventKey *event);
void		loop_intersect(t_data *ray, gboolean sh, t_obj *obj);
void		display_progress_bar(void);
void		pre_compute_tri(t_obj *o);
void		stereo_func(void);
void		oculus_func(void);
void		rotate_cam(int keyval);
void		move_cam(int keyval);
void		switch_key_focus(void);
void		*raytracing(void *arg);
void		put_pixel(int x, int y, t_color color);
void		get_norm(t_data *ray);
void		launch_thread(void);
void		init_view(void);
void		launch_preview(void);
void		desactivate_preview(void);
void		spin_button(void);
void		aa_check();
void		put_pixel_prev(int x, int y, t_color color);
void		sepia_filter();
void		greyscale_filter();
void		sobel_filter();
void		generate_perlin_tex(t_text *tex, float index);

#endif
