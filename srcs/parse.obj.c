/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 16:30:40 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/14 17:05:49 by bhuver           ###   ########.fr       */
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

void	load_obj(char **file, t_vect **v, int *i_s, t_obj *o)
{
	t_obj *new;

	while (file[i_s[0]] && !ft_sii(file[i_s[0]], "f "))
		++i_s[0];
	while (file[i_s[0]])
	{
		if (ft_sii(file[i_s[0]], "f ") &&
		check_tabsize(file[i_s[0]], i_s[1], i_s[2]))
		{
			new = malloc(sizeof(t_obj));
			read_triangle(new, file[i_s[0]], v, o->mater);
			set_func(new);
			push_to_obj(new, o);
		}
		++i_s[0];
	}
}

void	fill_values(char **file, int v_s, int vn_s, t_obj *new)
{
	t_vect	*v[2];
	int		i;
	int		in;

	i = 0;
	if (!v_s || !vn_s)
		return ;
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
	load_obj(file, v, (int[3]){i, v_s, vn_s}, new);
	free(v[0]);
	free(v[1]);
}

int		parse_obj(t_obj *new_mesh)
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
		while (get_next_line(fd, &line) && ++n < 9997)
		{
			file[n] = line;
			free(line);
		}
		free(line);
		file[n + 1] = 0;
		if ((n + 1) == 9998)
			return (0);
		count_values(file, &size[0], &size[1]);
		fill_values(file, size[0], size[1], new_mesh);
		ctab_free(file);
	}
	return (1);
}
