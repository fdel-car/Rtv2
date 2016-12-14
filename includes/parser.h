/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 18:45:50 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/14 15:11:38 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>

void		free_exit(void);
void		init_tex(t_text *tex);
void		free_objs(t_obj *o);
void		free_objects(gboolean all);
void		free_lights(void);
int			verif_type(t_obj *o);
void		free_objs(t_obj *o);
t_mater		load_material(char **t);
void		load_light2(t_light *new, char *s);
void		load_object3(t_obj *new, char *s);
void		load_object2(t_obj *new, char *s);
void		load_material2(t_mater *new, float *tsize, char *s);
int			start_by(char *s, char *end);
int			is_sim(char *t, char *s);
int			verif_file(char **t);
int			is_blank(char *l);
void		init_obj(t_obj *obj);
void		put_pixel_filter(int x, int y, t_color color);
void		add_torus_sphere(t_obj *o);
int			ft_limit(int v, int min, int max);
void		read_triangle(t_obj *o, char *line, t_vect **v, t_mater mat);
int			check_tabsize(char *line, int v_s, int vn_s);
void		init_gtk(void);
void		resize_texture(t_text *tex, float coef);
int			end_by(char *s, char *end);
int			count_esize(char **t);
t_text		*load_texture(char *path);
t_mater		init_mater(void);
char		*clean_line(char *s);
void		load_file(char *scene_file);
void		load_elems(char **t, unsigned char type);
void		load_camera(char **t);
int			ft_sii(char *s, char *e);
char		*get_after(char *s, char *a);
t_vect		read_vec(char *data, char op);
t_color		read_color(char *data);
void		ctab_free(char **t);
void		push_obj(t_obj *new);
void		push_to_obj(t_obj *new, t_obj *mesh_node);
void		push_lgt(t_light *new);
int			parse_obj(t_obj *new_mesh);
void		set_func(t_obj *o);
int			get_type(char *type);

#endif
