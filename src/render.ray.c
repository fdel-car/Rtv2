#include "rt.h"

t_color		diffuse_lighting(t_data *ray, t_light *l)
{
	t_color	c;
	float	cos;

	c = color_new(0, 0, 0);
	ray->light = vec_norm(vec_sub(l->pos, ray->hit_point));
	cos = vec_dotp(ray->light, ray->norm);
	if (cos > 0)
	{
		c = color_add(color_add(c, color_mult(l->color, l->intensity * cos))
		, color_mult((ray->obj_hit)->mater.color, l->intensity * cos));
	}
	return (c);
}

t_color		reflection_lighting(t_data *ray)
{
	t_data	refl;
	t_color	c;

	c = color_new(0, 0, 0);
	refl.dir = vec_mult(ray->norm, -2.0 * vec_dotp(ray->dir, ray->norm));
	refl.dir = vec_add(ray->dir, refl.dir);
	refl.orig = ray->hit_point;
	refl = intersect_obj(refl);
	if (refl.solut != -1)
		c = color_mult(refl.obj_hit->mater.color, 0.2);
	return (c);
}

// t_color		cast_reflection(t_data *ray)
// {
// 	t_color	c;
// 	t_data rfl;
//
// 	c = color_new(0, 0, 0);
// 	rfl.orig = ray->hit_point;
// 	rfl.dir = vec_mult(ray->norm, -2.0 * vec_dotp(ray->dir, ray->norm));
// 	rfl.dir = vec_add(ray->dir, rfl.dir);
// 	if (g_env.scene.iter_refl-- > 0)
// 		c = render_ray(intersect_obj(rfl));
// 	return (c);
// }

t_color		specular_lighting(t_data *ray, t_light *l)
{
	t_color	c;

	c = color_new(0, 0, 0);
	ray->refl = vec_norm(vec_sub(vec_mult(vec_mult(ray->norm,
	vec_dotp(ray->norm, ray->light)), 2.0), ray->light));
	if (vec_dotp(ray->light, ray->refl) > 0 && (ray->obj_hit)->type != PLANE)
	{
		c = color_add(c, color_mult(l->color,
		powf(vec_dotp(ray->light, ray->refl), (ray->obj_hit)->mater.shiny)));
	}
	return (c);
}

gboolean	is_shadowed(t_light *l, t_data *ray)
{
	t_data sh;
	t_vect tmp;

	ray->hit_point = vec_add(ray->orig, vec_mult(ray->dir, ray->solut));
	get_norm(ray);
	sh.orig = l->pos;
	sh.dir = vec_norm(vec_sub(ray->hit_point, l->pos));
	sh = intersect_obj(sh);
	tmp = vec_add(sh.orig, vec_mult(sh.dir, sh.solut));
	if (dist_p(tmp, l->pos) < dist_p(ray->hit_point, l->pos) - EPSILON)
		return (FALSE);
	return (TRUE);
}

t_color		compute_light(t_data ray)
{
	t_color		c;
	t_light		*l;
	gboolean	sh;

	l = g_env.scene.lgt;
	c = color_mult(ray.obj_hit->mater.color, 0.15);
	while (l)
	{
		sh = is_shadowed(l, &ray);
		if (ray.obj_hit->mater.int_refl > 0)
			c = color_add(c, reflection_lighting(&ray));
		if (sh != FALSE)
		{
			c = color_add(c, diffuse_lighting(&ray, l));
			c = color_add(c, specular_lighting(&ray, l));
		}
		l = l->next;
	}
	return (c);
}

t_color		render_ray(t_data ray)
{
	t_color color;

	if (ray.solut != -1 && ray.obj_hit)
	{
		color = compute_light(ray);
	}
	else
		color = color_new(0, 0, 0);
	return (color);
}
