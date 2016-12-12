/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 17:49:00 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/12 16:28:45 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		get_type(char *type)
{
	t_obj o;

	o.type = NONE;
	!ft_strcmp(type, "sphere") ? o.type = SPHERE : 0;
	!ft_strcmp(type, "mesh") ? o.type = MESH : 0;
	!ft_strcmp(type, "triangle") ? o.type = TRIANGLE : 0;
	!ft_strcmp(type, "cone") ? o.type = CONE : 0;
	!ft_strcmp(type, "cylinder") ? o.type = CYLINDER : 0;
	!ft_strcmp(type, "plane") ? o.type = PLANE : 0;
	!ft_strcmp(type, "dir_light") ? o.type = DIR_L : 0;
	!ft_strcmp(type, "point_light") ? o.type = POINT_L : 0;
	!ft_strcmp(type, "spot_light") ? o.type = SPOT_L : 0;
	!ft_strcmp(type, "skybox") ? o.type = SKYBOX : 0;
	return (o.type);
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
	free(vals);
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
	free(vals);
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
