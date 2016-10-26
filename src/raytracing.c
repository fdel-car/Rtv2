/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 17:53:11 by fdel-car          #+#    #+#             */
/*   Updated: 2016/10/26 16:20:03 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_data		intersect_obj(t_data ray)
{
	t_obj	*obj;
	float	tmp;

	ray.solut = -1;
	ray.obj_hit = NULL;
	obj = g_env.scene.obj;
	while (obj)
	{
		tmp = (*obj->func)(obj, ray);
		if ((tmp < ray.solut || ray.solut == -1) && tmp != -1)
		{
			ray.obj_hit = obj;
			ray.solut = tmp;
		}
		obj = obj->next;
	}
	return (ray);
}

void		init_view(void)
{
	g_env.scene.cam.up = vec_new(0, 1, 0);
	g_env.scene.cam.view_d = 1.5;
	g_env.scene.cam.view_h = 1.4;
	g_env.scene.cam.view_w = 2.4;
	g_env.scene.cam.x_ind = g_env.scene.cam.view_w / (float)WIDTH;
	g_env.scene.cam.y_ind = g_env.scene.cam.view_h / (float)HEIGHT;
}

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
		if (sh != FALSE)
		{
			c = color_add(c, diffuse_lighting(&ray, l));
			c = color_add(c, specular_lighting(&ray, l));
		}
		l = l->next;
	}
	return (c);
}

void		render_ray(t_data ray, int x, int y)
{
	t_color color;

	if (ray.solut != -1 && ray.obj_hit)
	{
		color = compute_light(ray);
		put_pixel(x, y, color);
	}
	else
		put_pixel(x, y, color_new(0, 0, 0));
}

void		*raytracing(void *arg)
{
	int		*tmp;
	int		x, x_max, y;
	t_vect	view_point;
	t_data	ray;

	tmp = (int *)arg;
	x = *tmp;
	x_max = x + WIDTH / NUM_THREAD;
	ray.orig = g_env.scene.cam.pos;
	while (x < x_max)
	{
		y = 0;
		while (y < HEIGHT)
		{
			view_point = vec_sub(vec_add(g_env.scene.cam.up_left,
			vec_mult(g_env.scene.cam.right,
			g_env.scene.cam.x_ind * x)), vec_mult(g_env.scene.cam.up,
			g_env.scene.cam.y_ind * y));
			ray.dir = vec_norm(vec_sub(view_point, g_env.scene.cam.pos));
			render_ray(intersect_obj(ray), x, y);
			y++;
		}
		x++;
	}
	pthread_exit(NULL);
}
