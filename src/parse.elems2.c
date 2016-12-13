/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.elems2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 20:30:30 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/13 20:30:52 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

void	load_material2(t_mater *new, float *tsize, char *s)
{
	if (ft_sii(s, "brillance:"))
		new->shiny = ft_atof(get_after(s, "brillance:"));
	if (ft_sii(s, "reflection:"))
		new->int_refl = ft_atof(get_after(s, "reflection:"));
	if (ft_sii(s, "transparence:"))
		new->int_trans = ft_atof(get_after(s, "transparence:"));
	if (ft_sii(s, "indice:"))
		new->indice = ft_atof(get_after(s, "indice:"));
	if (ft_sii(s, "tsize:"))
		*tsize = ft_atof(get_after(s, "tsize:"));
	if (ft_sii(s, "color:"))
		new->color = read_color(get_after(s, "color:"));
	if (ft_sii(s, "texture:"))
		new->tex = load_texture(get_after(s, "texture:"));
	if (ft_sii(s, "ntext:"))
		new->ntex = load_texture(get_after(s, "ntext:"));
	if (ft_sii(s, "ttext:"))
		new->ttex = load_texture(get_after(s, "ttext:"));
	if (ft_sii(s, "ctext:"))
		new->ctex = load_texture(get_after(s, "ctext:"));
}

void	load_object2(t_obj *new, char *s)
{
	if (ft_sii(s, "v0:"))
		new->v0 = read_vec(get_after(s, "v0:"), ';');
	if (ft_sii(s, "v1:"))
		new->v1 = read_vec(get_after(s, "v1:"), ';');
	if (ft_sii(s, "v2:"))
		new->v2 = read_vec(get_after(s, "v2:"), ';');
	if (ft_sii(s, "pos:"))
		new->pos = read_vec(get_after(s, "pos:"), ';');
	if (ft_sii(s, "cut_dir:"))
		new->cut = vec_norm(read_vec(get_after(s, "cut_dir:"), ';'));
	if (ft_sii(s, "cut_center:"))
		new->cut_pos = read_vec(get_after(s, "cut_center:"), ';');
	if (ft_sii(s, "sphere_cut:"))
		new->sphere_cut = ft_atof(get_after(s, "sphere_cut:"));
	if (ft_sii(s, "dir:"))
		new->dir = vec_norm(read_vec(get_after(s, "dir:"), ';'));
}

void	load_object3(t_obj *new, char *s)
{
	if (ft_sii(s, "min:"))
		new->min = ft_atof(get_after(s, "min:"));
	if (ft_sii(s, "max:"))
		new->max = ft_atof(get_after(s, "max:"));
	if (ft_sii(s, "rayon:"))
		new->rayon = ft_atof(get_after(s, "rayon:"));
	if (ft_sii(s, "alpha:"))
		new->alpha = ft_atof(get_after(s, "alpha:")) * M_PI / 180;
	if (new->alpha > 1.5707 || new->alpha == 0)
		new->alpha = 1.5707;
	if (ft_sii(s, "type:"))
		new->type = get_type(get_after(s, "type:"));
	if (ft_sii(s, "normal:"))
		new->norm = vec_norm(read_vec(get_after(s, "normal:"), ';'));
	if (ft_sii(s, "src:"))
		new->src = ft_strdup(get_after(s, "src:"));
}

void	load_light2(t_light *new, char *s)
{
	if (ft_sii(s, "pos:"))
		new->pos = read_vec(get_after(s, "pos:"), ';');
	if (ft_sii(s, "dir:"))
		new->dir = vec_norm(read_vec(get_after(s, "dir:"), ';'));
	if (ft_sii(s, "rayon:"))
		new->rayon = ft_atof(get_after(s, "rayon:"));
	if (ft_sii(s, "alpha:"))
		new->alpha = ft_atof(get_after(s, "alpha:")) * M_PI / 180;
	if (new->alpha > 1.5707 || new->alpha == 0)
		new->alpha = 1.5707;
	if (ft_sii(s, "type:"))
		new->type = get_type(get_after(s, "type:"));
	if (ft_sii(s, "color:"))
		new->color = read_color(get_after(s, "color:"));
	if (ft_sii(s, "intensity:"))
		new->intensity = ft_atof(get_after(s, "intensity:"));
	if (ft_sii(s, "blur:"))
		new->blur = ft_atoi(get_after(s, "blur:"));
}
