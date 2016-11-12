/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 18:45:50 by fdel-car          #+#    #+#             */
/*   Updated: 2016/11/12 18:36:19 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>

t_text		load_texture(char *path);
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

// print
void		print_lgt();
void		print_obj();

// test affichage texture
void		test_texture(t_text tex);

#endif
