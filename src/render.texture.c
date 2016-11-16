#include "rt.h"

int		ft_limit(int v, int min, int max)
{
	v > max ? v = max : 0;
	v < min ? v = min : 0;
	return (v);
}

t_color	get_texture(t_data ray)
{
	t_vect	d;
	float	u;
	float	v;
	int		i;
	int		j;
	t_color	r;

	if (!ray.obj_hit || !ray.obj_hit->mater.tex)
		return (ray.obj_hit->mater.color);
	d = vec_norm(vec_sub(ray.hit_point, ray.obj_hit->pos));
	u = 0.5 + atan2(d.z, d.x) / M_PI * 0.5;
	v = 0.5 - asin(d.y) / M_PI;
	i = ft_limit(u * ray.obj_hit->mater.tex->tex_w, 0, ray.obj_hit->mater.tex->tex_w - 1);
	j = ft_limit(v * ray.obj_hit->mater.tex->tex_h, 0, ray.obj_hit->mater.tex->tex_h - 1);
	r.r = ray.obj_hit->mater.tex->text[j *
	(ray.obj_hit->mater.tex->tex_w * 3) + (i * 3)];
	r.g = ray.obj_hit->mater.tex->text[j *
	(ray.obj_hit->mater.tex->tex_w * 3) + (i * 3) + 1];
	r.b = ray.obj_hit->mater.tex->text[j *
	(ray.obj_hit->mater.tex->tex_w * 3) + (i * 3) + 2];
	return (r);
}
