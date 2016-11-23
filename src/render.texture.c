#include "rt.h"

t_color	get_resize_pxl(t_text *tex, float coef, int x, int y)
{
	t_color	c;
	int		old_x;
	int		old_y;
	int		pos;

	old_x = x / coef;
	old_y = y / coef;
	pos = old_y * tex->tex_w * 3 + old_x * 3;
	c.r = tex->text[pos];
	c.g = tex->text[pos + 1];
	c.b = tex->text[pos + 2];
	return (c);
}

void	resize_texture(t_text *tex, float coef)
{
	unsigned char	*tmp;
	int				x;
	int				x_max;
	int				y;
	int				y_max;
	int				pos;
	t_color			c;

	if (!tex)
		return ;
	x_max = tex->tex_w * coef;
	y_max = tex->tex_h * coef;
	tmp = (unsigned char *)malloc(sizeof(unsigned char) * x_max * 3 * y_max);
	pos = 0;
	y = 0;
	while (y < y_max)
	{
		x = 0;
		while (x < x_max)
		{
			c = get_resize_pxl(tex, coef, x, y);
			tmp[pos++] = c.r;
			tmp[pos++] = c.g;
			tmp[pos++] = c.b;
			x++;
		}
		y++;
	}
	free(tex->text);
	tex->text = tmp;
	tex->tex_w = x_max;
	tex->tex_h = y_max;
}

int			ft_limit(int v, int min, int max)
{
	v > max ? v = max : 0;
	v < min ? v = min : 0;
	return (v);
}

t_color		get_texel(t_text tex, int i, int j)
{
	t_color	r;

	r.r = tex.text[j *
	(tex.tex_w * 3) + (i * 3)];
	r.g = tex.text[j *
	(tex.tex_w * 3) + (i * 3) + 1];
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

	scale = 1;
	u_axis = vec_new(ray.norm.y, ray.norm.z, -ray.norm.x);
	v_axis = cross_pr(u_axis, ray.obj_hit->norm);
	u = vec_dotp(ray.hit_point, u_axis) * scale;
	v = vec_dotp(ray.hit_point, v_axis) * scale;
	u = u - floor(u);
	v = v - floor(v);

	return (get_texel(*tex,
	v * (tex->tex_h - 1),
	u * (tex->tex_w - 1)));
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
	float	u;
	float	v;
	int		i;
	int		j;

	d = vec_sub(ray.hit_point, vec_mul(ray.obj_hit->pos, ray.obj_hit->dir));
	u = 0.5 + atan2(d.z, d.x) / M_PI * 0.5;
	v = d.y / 10; // 10 correspond a la hauteur du repeat de la texture
	v = v - floor(v);
	i = ft_limit(u * tex->tex_w, 0, tex->tex_w - 1);
	j = ft_limit(v * tex->tex_h, 0, tex->tex_h - 1);
	return (get_texel(*tex, i, j));
}

t_color		get_texture(t_data ray)
{
	t_color r;

	r = ray.obj_hit->mater.color;
	if (!ray.obj_hit->mater.tex)
		return (r);
	if (ray.obj_hit->type == SPHERE || ray.obj_hit->type == SKYBOX)
		return (getex_sphere(ray, ray.obj_hit->mater.tex));
	if (ray.obj_hit->type == PLANE)
		return (getex_plane(ray, ray.obj_hit->mater.tex));
	if (ray.obj_hit->type == CYLINDER ||
	ray.obj_hit->type == CONE)
		return (getex_cyl(ray, ray.obj_hit->mater.tex));
	return (r);
}
