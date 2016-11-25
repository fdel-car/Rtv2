/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 16:30:40 by fdel-car          #+#    #+#             */
/*   Updated: 2016/11/25 16:36:30 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	count_values(char **file, int *v_size, int *vn_size)
{
	int i;

	i = 0;
	while (file[i] && !ft_sii(file[i], "v "))
		++i;
	while (file[i] && ft_sii(file[i], "v "))
	{
		(*v_size)++;
		++i;
	}
	while (file[i] && !ft_sii(file[i], "vn "))
		++i;
	while (file[i] && ft_sii(file[i++], "vn "))
		(*vn_size)++;
}

void	load_obj(char **file, t_vect **v, int i, t_obj *o)
{
	t_obj *new;

	while (file[i] && !ft_sii(file[i], "f "))
		++i;
	while (file[i])
	{
		new = malloc(sizeof(t_obj));
		read_triangle(new, file[i], v, o->mater);
		set_func(new);
		push_to_obj(new, o);
		++i;
	}
}

void	fill_values(char **file, int v_s, int vn_s, t_obj *new)
{
	t_vect	*v[2];
	int		i;
	int		in;

	i = 0;
	v[0] = malloc(sizeof(t_vect) * (v_s + 1));
	v[1] = malloc(sizeof(t_vect) * (vn_s + 1));
	while (file[i] && !ft_sii(file[i], "v "))
		++i;
	in = 0;
	while (file[i] && ft_sii(file[i], "v "))
		v[0][in++] = read_vec(get_after(file[i++], "v "), ' ');
	while (file[i] && !ft_sii(file[i], "vn "))
		++i;
	in = 0;
	while (file[i] && ft_sii(file[i], "vn "))
		v[1][in++] = read_vec(get_after(file[i++], "vn "), ' ');
	load_obj(file, v, i, new);
	free(v[0]);
	free(v[1]);
}

void	parse_obj(t_obj *new_mesh)
{
	int		fd;
	char	*line;
	char	*file[9999];
	int		n;
	int		size[2];

	n = -1;
	size[0] = 0;
	size[1] = 0;
	if ((fd = open(new_mesh->src, O_RDONLY)) >= 0)
	{
		while (get_next_line(fd, &line) && (++n) > -42)
			file[n] = line;
		file[n + 1] = 0;
		count_values(file, &size[0], &size[1]);
		fill_values(file, size[0], size[1], new_mesh);
		ctab_free(file);
	}
}
