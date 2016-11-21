/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.elems.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 17:44:04 by fdel-car          #+#    #+#             */
/*   Updated: 2016/11/21 18:21:20 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_mater	load_material(char **t)
{
	t_mater	new;
	int		n;

	n = 1;
	new = init_mater();
	if (ft_sii(t[n], "{"))
		while (t[++n] && !ft_sii(t[n], "{"))
		{
			if (ft_sii(t[n], "brillance:"))
				new.shiny = ft_atof(get_after(t[n], "brillance:"));
			if (ft_sii(t[n], "reflection:"))
				new.int_refl = ft_atof(get_after(t[n], "reflection:"));
			if (ft_sii(t[n], "transparence:"))
				new.int_trans = ft_atof(get_after(t[n], "transparence:"));
			if (ft_sii(t[n], "color:"))
				new.color = read_color(get_after(t[n], "color:"));
			if (ft_sii(t[n], "texture:"))
				new.tex = load_texture(get_after(t[n], "texture:"));
		}
	return (new);
}

void	set_func(t_obj *o)
{
	if (o->type == SPHERE)
		o->func = &intersect_sphere;
	if (o->type == SKYBOX)
		o->func = &intersect_sphere;
	if (o->type == PLANE)
		o->func = &intersect_plane;
	if (o->type == CYLINDER)
		o->func = &intersect_cylinder;
	if (o->type == CONE)
		o->func = &intersect_cone;
	if (o->type == TRIANGLE)
		o->func = &intersect_triangle;
}

void	load_object(char **t)
{
	t_obj	*new;
	char	*name;
	int		n;

	new = malloc(sizeof(t_obj));
	new->next = NULL;
	new->src = NULL;
	name = ft_strdup(*t);
	new->name = ft_strtrim(name);
	new->cut = vec_new(0, 0, 0);
	new->min = 0;
	new->max = 0;
	free(name);
	if ((n = 1) && ft_sii(t[n], "{"))
		while (t[++n] && !ft_sii(t[n], "{"))
		{
			if (ft_sii(t[n], "v0:"))
				new->v0 = read_vec(get_after(t[n], "v0:"), ';');
			if (ft_sii(t[n], "v1:"))
				new->v1 = read_vec(get_after(t[n], "v1:"), ';');
			if (ft_sii(t[n], "v2:"))
				new->v2 = read_vec(get_after(t[n], "v2:"), ';');
			if (ft_sii(t[n], "pos:"))
				new->pos = read_vec(get_after(t[n], "pos:"), ';');
			if (ft_sii(t[n], "cut:"))
				new->cut = vec_norm(read_vec(get_after(t[n], "cut:"), ';'));
			if (ft_sii(t[n], "dir:"))
				new->dir = vec_norm(read_vec(get_after(t[n], "dir:"), ';'));
			if (ft_sii(t[n], "min:"))
				new->min = ft_atof(get_after(t[n], "min:"));
			if (ft_sii(t[n], "max:"))
				new->max = ft_atof(get_after(t[n], "max:"));
			if (ft_sii(t[n], "rayon:"))
				new->rayon = ft_atof(get_after(t[n], "rayon:"));
			if (ft_sii(t[n], "alpha:"))
				new->alpha = ft_atof(get_after(t[n], "alpha:")) * M_PI / 180;
			if (new->alpha > 1.5707)
				new->alpha = 1.5707;
			if (ft_sii(t[n], "type:"))
				new->type = get_type(get_after(t[n], "type:"));
			if (ft_sii(t[n], "normal:"))
				new->norm = vec_norm(read_vec(get_after(t[n], "normal:"), ';'));
			if (ft_sii(t[n], "materiel"))
				new->mater = load_material(&(t[n]));
			if (ft_sii(t[n], "src:"))
				new->src = ft_strdup(get_after(t[n], "src:"));
		}
	if (new->src)
		parse_obj(new);
	set_func(new);
	push_obj(new);
}

void	load_light(char **t)
{
	t_light	*new;
	char	*name;
	int		n;

	n = 1;
	new = malloc(sizeof(t_light));
	new->next = NULL;
	name = ft_strdup(*t);
	new->name = ft_strtrim(name);
	free(name);
	if (ft_sii(t[n], "{"))
		while (t[++n] && !ft_sii(t[n], "{"))
		{
			if (ft_sii(t[n], "pos:"))
				new->pos = read_vec(get_after(t[n], "pos:"), ';');
			if (ft_sii(t[n], "dir:"))
				new->dir = vec_norm(read_vec(get_after(t[n], "dir:"), ';'));
			if (ft_sii(t[n], "rayon:"))
				new->rayon = ft_atof(get_after(t[n], "rayon:"));
			if (ft_sii(t[n], "type:"))
				new->type = get_type(get_after(t[n], "type:"));
			if (ft_sii(t[n], "color:"))
				new->color = read_color(get_after(t[n], "color:"));
			if (ft_sii(t[n], "intensity:"))
				new->intensity = ft_atof(get_after(t[n], "intensity:"));
			if (ft_sii(t[n], "blur:"))
				new->blur = ft_atoi(get_after(t[n], "blur:"));
		}
	push_lgt(new);
}

void	load_elems(char **t, unsigned char type)
{
	int	n;

	n = 0;
	while (t[n])
	{
		if (!ft_strcmp(clean_line(t[n]), "}"))
			break ;
		type == 'l' ?
			load_light(&(t[n])) : load_object(&(t[n]));
		++n;
		if (!ft_strcmp(clean_line(t[n]), "{") && ++n)
			while (t[n] && ft_strcmp(clean_line(t[n]), "}"))
				++n;
		n += type == 'l' ? 1 : 2;
	}
}
