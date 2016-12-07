/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 18:45:50 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/07 15:04:54 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>

void		init_obj(t_obj *obj);
void		put_pixel_filter(int x, int y, t_color color);
void		add_torus_sphere(t_obj *o);
int			ft_limit(int v, int min, int max);
void		read_triangle(t_obj *o, char *line, t_vect **v, t_mater mat);
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
void		parse_obj(t_obj *new_mesh);
void		set_func(t_obj *o);
e_type		get_type(char *type);

#endif
