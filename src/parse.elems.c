/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.elems.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 17:44:04 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/12 16:10:09 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_mater	load_material(char **t)
{
	t_mater	new;
	int		n;
	int		se;
	float	tsize;

	n = 1;
	tsize = -42;
	new = init_mater();
	se = count_esize(&(t[n]));
	if (ft_sii(t[n], "{"))
		while (t[++n] && --se > 1)
		{
			if (ft_sii(t[n], "brillance:"))
				new.shiny = ft_atof(get_after(t[n], "brillance:"));
			if (ft_sii(t[n], "reflection:"))
				new.int_refl = ft_atof(get_after(t[n], "reflection:"));
			if (ft_sii(t[n], "transparence:"))
				new.int_trans = ft_atof(get_after(t[n], "transparence:"));
			if (ft_sii(t[n], "indice:"))
				new.indice = ft_atof(get_after(t[n], "indice:"));
			if (ft_sii(t[n], "tsize:"))
				tsize = ft_atof(get_after(t[n], "tsize:"));
			if (ft_sii(t[n], "color:"))
				new.color = read_color(get_after(t[n], "color:"));
			if (ft_sii(t[n], "texture:"))
				new.tex = load_texture(get_after(t[n], "texture:"));
			if (ft_sii(t[n], "ntext:"))
				new.ntex = load_texture(get_after(t[n], "ntext:"));
			if (ft_sii(t[n], "ttext:"))
				new.ttex = load_texture(get_after(t[n], "ttext:"));
			if (ft_sii(t[n], "ctext:"))
				new.ctex = load_texture(get_after(t[n], "ctext:"));
		}
	if (new.tex)
		new.tex->tsize = tsize > 0 ? tsize : -42;
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

void	init_obj(t_obj *obj)
{
	obj->next = NULL;
	obj->src = NULL;
	obj->cut = vec_new(0, 0, 0);
	obj->min = 0;
	obj->max = 0;
	obj->sphere_cut = 0;
	obj->lst = NULL;
	obj->mater = init_mater();
	obj->name = NULL;
}

void	load_object(char **t)
{
	t_obj	*new;
	char	*name;
	int		n;
	int		se;

	new = malloc(sizeof(t_obj));
	init_obj(new);
	name = ft_strdup(*t);
	new->name = ft_strtrim(name);
	se = count_esize(&(t[1]));
	free(name);
	if ((n = 1) && ft_sii(t[n], "{"))
		while (t[++n] && --se > 1)
		{
			if (ft_sii(t[n], "v0:"))
				new->v0 = read_vec(get_after(t[n], "v0:"), ';');
			if (ft_sii(t[n], "v1:"))
				new->v1 = read_vec(get_after(t[n], "v1:"), ';');
			if (ft_sii(t[n], "v2:"))
				new->v2 = read_vec(get_after(t[n], "v2:"), ';');
			if (ft_sii(t[n], "pos:"))
				new->pos = read_vec(get_after(t[n], "pos:"), ';');
			if (ft_sii(t[n], "cut_dir:"))
				new->cut = vec_norm(read_vec(get_after(t[n], "cut_dir:"), ';'));
			if (ft_sii(t[n], "cut_center:"))
				new->cut_pos = read_vec(get_after(t[n], "cut_center:"), ';');
			if (ft_sii(t[n], "sphere_cut:"))
				new->sphere_cut = ft_atof(get_after(t[n], "sphere_cut:"));
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
			if (new->alpha > 1.5707 || new->alpha == 0)
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
	int		se;

	n = 1;
	new = malloc(sizeof(t_light));
	new->next = NULL;
	name = ft_strdup(*t);
	se = count_esize(&(t[n]));
	new->name = ft_strtrim(name);
	free(name);
	if (ft_sii(t[n], "{"))
		while (t[++n] && --se > 1)
		{
			if (ft_sii(t[n], "pos:"))
				new->pos = read_vec(get_after(t[n], "pos:"), ';');
			if (ft_sii(t[n], "dir:"))
				new->dir = vec_norm(read_vec(get_after(t[n], "dir:"), ';'));
			if (ft_sii(t[n], "rayon:"))
				new->rayon = ft_atof(get_after(t[n], "rayon:"));
			if (ft_sii(t[n], "alpha:"))
				new->alpha = ft_atof(get_after(t[n], "alpha:")) * M_PI / 180;
			if (new->alpha > 1.5707 || new->alpha == 0)
				new->alpha = 1.5707;
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
	int	se;
	int tmp;
	int	nb;

	n = 1;
	se = count_esize(t);
	while (t[n] && --se > 1)
	{
		nb = n;
		while (is_blank(t[nb]))
			nb++;
		nb = nb - n;
		n += nb;
		se -= nb;
		type == 'l' ?
			load_light(&(t[n])) : load_object(&(t[n]));
		++n;
		tmp = count_esize(&(t[n]));
		n += tmp;
		se -= tmp;
	}
}
