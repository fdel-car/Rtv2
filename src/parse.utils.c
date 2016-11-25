/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 17:49:00 by fdel-car          #+#    #+#             */
/*   Updated: 2016/11/25 16:37:42 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

e_type	get_type(char *type)
{
	e_type	t;

	t = NONE;
	!ft_strcmp(type, "sphere") ? t = SPHERE : 0;
	!ft_strcmp(type, "mesh") ? t = MESH : 0;
	!ft_strcmp(type, "triangle") ? t = TRIANGLE : 0;
	!ft_strcmp(type, "cone") ? t = CONE : 0;
	!ft_strcmp(type, "cylinder") ? t = CYLINDER : 0;
	!ft_strcmp(type, "plane") ? t = PLANE : 0;
	!ft_strcmp(type, "dir_light") ? t = DIR_L : 0;
	!ft_strcmp(type, "point_light") ? t = POINT_L : 0;
	!ft_strcmp(type, "skybox") ? t = SKYBOX : 0;
	return (t);
}

t_color	read_color(char *data)
{
	t_color	new;
	char	**vals;

	new = color_new(0, 0, 0);
	if (!ft_strcmp(data, "NULL"))
		return (new);
	vals = ft_strsplit(data, ';');
	if (vals[0] && vals[1] && vals[2])
	{
		new.r = ft_atoi(vals[0]);
		new.g = ft_atoi(vals[1]);
		new.b = ft_atoi(vals[2]);
	}
	ctab_free(vals);
	return (new);
}

t_vect	read_vec(char *data, char op)
{
	t_vect	new;
	char	**vals;

	new = vec_new(0, 0, 0);
	if (!ft_strcmp(data, "NULL"))
		return (new);
	vals = ft_strsplit(data, op);
	if (vals[0] && vals[1] && vals[2])
	{
		new.x = ft_atof(vals[0]);
		new.y = ft_atof(vals[1]);
		new.z = ft_atof(vals[2]);
	}
	ctab_free(vals);
	return (new);
}

int		ft_sii(char *s, char *e)
{
	int	is;
	int	ie;

	is = -1;
	while (s[++is])
	{
		ie = 0;
		while (s[is + ie] && e[ie] &&
				s[is + ie] == e[ie])
			++ie;
		if (!e[ie])
			return (1);
	}
	return (0);
}

int		end_by(char *s, char *end)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (s[++i])
		;
	while (end[++j])
		;
	i--;
	j--;
	while (j >= 0 && end[j] && s[i])
	{
		if (s[i] != end[j])
			return (0);
		j--;
		i--;
	}
	return (1);
}
