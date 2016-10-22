/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 18:45:50 by fdel-car          #+#    #+#             */
/*   Updated: 2016/10/22 16:32:06 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>

//init elems
t_mater   init_mater(void);

//utils
char      *clean_line(char *s);

void      load_file(char *scene_file);
void      load_elems(char **t, unsigned char type);
void      load_camera(char **t);
int       ft_sii(char *s, char *e);// return if e is in s
char      *get_after(char *s, char *a);//return the substring of s wich is after the substring a
t_vect    read_vec(char *data);
t_color   read_color(char *data);
void      ctab_free(char **t);

void      push_obj(t_obj *new);
void      push_lgt(t_light *new);

void       print_lgt();
void       print_obj();


#endif
