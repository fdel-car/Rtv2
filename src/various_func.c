/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   various_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 16:54:33 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/11 18:50:50 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	put_pixel(int x, int y, t_color color)
{
	int pos;

	pos = y * g_env.rowstride + x * 3;
	g_env.pixels[pos] = color.r;
	g_env.pixels[pos + 1] = color.g;
	g_env.pixels[pos + 2] = color.b;
}

t_vect	refract_dir_bis(t_data *ray, t_obj *obj, float n, float cos)
{
	float	disc;

	disc = 1 - (pow(n, 2) * (1 - pow(cos, 2)));
	if (disc < 0 && obj->type != OCULUS)
	{
		return (vec_sub(ray->dir, vec_mult(ray->norm, 2 * vec_dotp(ray->dir,
		ray->norm))));
	}
	return (vec_add(vec_mult(ray->dir, n), vec_mult(ray->norm,
	((n * cos) - sqrt(disc)))));
}

void	pre_compute_tri(t_obj *o)
{
	t_obj *tmp;

	while (o)
	{
		if (o->type == TRIANGLE)
		{
			o->u = vec_sub(o->v1, o->v0);
			o->v = vec_sub(o->v2, o->v0);
		}
		if (o->type == MESH)
		{
			tmp = o->lst;
			while (tmp)
			{
				if (tmp->type == TRIANGLE)
				{
					tmp->u = vec_sub(tmp->v1, tmp->v0);
					tmp->v = vec_sub(tmp->v2, tmp->v0);
				}
				tmp = tmp->next;
			}
		}
		o = o->next;
	}
}

void	stereo_func(void)
{
	if (g_env.stereo_red == TRUE)
	{
		red_filter();
		g_env.stereo_red = FALSE;
		g_env.scene.cam.pos = vec_add(g_env.scene.cam.pos,
		vec_mult(g_env.scene.cam.right, DIST_INTEROCULAR));
		g_env.scene.cam.dir = vec_norm(vec_sub(g_env.scene.cam.look_at,
		g_env.scene.cam.pos));
		launch_thread();
	}
	else
	{
		g_env.scene.cam.pos = vec_sub(g_env.scene.cam.pos,
		vec_mult(g_env.scene.cam.right, DIST_INTEROCULAR / 2));
		g_env.scene.cam.dir = vec_norm(vec_sub(g_env.scene.cam.look_at,
		g_env.scene.cam.pos));
		green_blue_filter();
		g_env.stereo_red = TRUE;
		gtk_image_set_from_pixbuf(GTK_IMAGE(g_env.img), g_env.filter);
	}
}

void	oculus_func(void)
{
	if (g_env.oculus_left == TRUE)
	{
		g_env.oculus_left = FALSE;
		g_env.scene.cam.pos = vec_add(g_env.scene.cam.pos,
		vec_mult(g_env.scene.cam.right, DIST_INTEROCULAR));
		g_env.scene.cam.dir = vec_norm(vec_sub(g_env.scene.cam.look_at,
		g_env.scene.cam.pos));
		left_filter();
		launch_thread();
	}
	else
	{
		g_env.scene.cam.pos = vec_sub(g_env.scene.cam.pos,
		vec_mult(g_env.scene.cam.right, DIST_INTEROCULAR / 2));
		g_env.scene.cam.dir = vec_norm(vec_sub(g_env.scene.cam.look_at,
		g_env.scene.cam.pos));
		right_filter();
		g_env.oculus_left = TRUE;
		gtk_image_set_from_pixbuf(GTK_IMAGE(g_env.img), g_env.filter);
	}
}
