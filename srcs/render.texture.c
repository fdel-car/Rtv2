/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 16:53:40 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/12 16:35:25 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color		get_texel(t_text tex, int i, int j)
{
	t_color	r;

	r = color_new(0, 0, 0);
	if (i < 0 || j < 0)
		return (r);
	if (j * (tex.tex_w * 3) + (i * 3) <
	tex.tex_h * tex.tex_w * 3)
		r.r = tex.text[j *
		(tex.tex_w * 3) + (i * 3)];
	if (j * (tex.tex_w * 3) + (i * 3) + 1 <
	tex.tex_h * tex.tex_w * 3)
		r.g = tex.text[j *
		(tex.tex_w * 3) + (i * 3) + 1];
	if (j * (tex.tex_w * 3) + (i * 3) + 1 <
	tex.tex_h * tex.tex_w * 3)
		r.b = tex.text[j *
		(tex.tex_w * 3) + (i * 3) + 2];
	return (r);
}

t_color		getex_plane(t_data ray, t_text *tex)
{
	float	u;
	float	v;
	t_vect	u_axis;
	t_vect	v_axis;
	float	scale;

	scale = tex->tsize > 0 ? tex->tsize : 0.1;
	u_axis = vec_new(ray.norm.y, ray.norm.z, -ray.norm.x);
	v_axis = cross_pr(u_axis, ray.obj_hit->norm);
	u = vec_dotp(ray.hit_point, u_axis) * scale;
	v = vec_dotp(ray.hit_point, v_axis) * scale;
	u = u - floor(u);
	v = v - floor(v);
	return (get_texel(*tex, v * (tex->tex_h - 1), u * (tex->tex_w - 1)));
}

t_color		getex_sphere(t_data ray, t_text *tex)
{
	t_vect	d;
	float	u;
	float	v;
	int		i;
	int		j;

	if (!ray.obj_hit || !tex)
		return (ray.obj_hit->mater.color);
	d = vec_norm(vec_sub(ray.hit_point, ray.obj_hit->pos));
	u = 0.5 + atan2(d.z, d.x) / M_PI * 0.5;
	v = 0.5 - asin(d.y) / M_PI;
	i = ft_limit(u * tex->tex_w, 0, tex->tex_w - 1);
	j = ft_limit(v * tex->tex_h, 0, tex->tex_h - 1);
	return (get_texel(*tex, i, j));
}

t_color		getex_cyl(t_data ray, t_text *tex)
{
	t_vect	d;
	float	v[3];
	int		i;
	int		j;

	v[2] = tex->tsize > 0 ? tex->tsize : 10;
	d = vec_sub(ray.hit_point, vec_mul(ray.obj_hit->pos, ray.obj_hit->dir));
	v[0] = 0.5 + atan2(d.z, d.x) / M_PI * 0.5;
	v[1] = d.y / tex->tsize;
	v[1] = v[1] - floor(v[1]);
	i = ft_limit(v[0] * tex->tex_w, 0, tex->tex_w - 1);
	j = ft_limit(v[1] * tex->tex_h, 0, tex->tex_h - 1);
	return (get_texel(*tex, i, j));
}

t_color		get_texture(t_data ray, t_text *tex)
{
	t_color r;

	r = ray.obj_hit->mater.color;
	if (!tex)
		return (r);
	if (ray.obj_hit->type == SPHERE || ray.obj_hit->type == SKYBOX)
		return (getex_sphere(ray, tex));
	if (ray.obj_hit->type == PLANE)
		return (getex_plane(ray, tex));
	if (ray.obj_hit->type == CYLINDER ||
	ray.obj_hit->type == CONE)
		return (getex_cyl(ray, tex));
	return (r);
}
