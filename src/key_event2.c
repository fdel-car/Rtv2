/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 16:42:29 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/11 16:47:56 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		move_cam_bis(int keyval)
{
	if (keyval == 97)
	{
		g_env.scene.cam.pos = vec_add(g_env.scene.cam.pos,
		rot_any(g_env.scene.cam.dir, g_env.scene.cam.up, -90));
		g_env.scene.cam.look_at = vec_add(g_env.scene.cam.look_at,
		rot_any(g_env.scene.cam.dir, g_env.scene.cam.up, -90));
	}
	if (keyval == 100)
	{
		g_env.scene.cam.pos = vec_add(g_env.scene.cam.pos,
		rot_any(g_env.scene.cam.dir, g_env.scene.cam.up, 90));
		g_env.scene.cam.look_at = vec_add(g_env.scene.cam.look_at,
		rot_any(g_env.scene.cam.dir, g_env.scene.cam.up, 90));
	}
}

void		move_cam(int keyval)
{
	if (keyval == 32)
	{
		g_env.scene.cam.pos = vec_add(g_env.scene.cam.pos,
		rot_any(g_env.scene.cam.dir, g_env.scene.cam.right, -90));
		g_env.scene.cam.look_at = vec_add(g_env.scene.cam.look_at,
		rot_any(g_env.scene.cam.dir, g_env.scene.cam.right, -90));
	}
	if (keyval == 99)
	{
		g_env.scene.cam.pos = vec_add(g_env.scene.cam.pos,
		rot_any(g_env.scene.cam.dir, g_env.scene.cam.right, 90));
		g_env.scene.cam.look_at = vec_add(g_env.scene.cam.look_at,
		rot_any(g_env.scene.cam.dir, g_env.scene.cam.right, 90));
	}
	move_cam_bis(keyval);
}

void		rotate_cam_bis(int keyval)
{
	if (keyval == 65362)
	{
		g_env.scene.cam.dir = vec_norm(rot_any(g_env.scene.cam.dir,
		g_env.scene.cam.right, -9));
		g_env.scene.cam.up = cross_pr(g_env.scene.cam.dir,
		g_env.scene.cam.right);
		g_env.scene.cam.look_at = vec_add(g_env.scene.cam.pos,
		vec_mult(g_env.scene.cam.dir, g_env.scene.cam.dist));
	}
	if (keyval == 65364)
	{
		g_env.scene.cam.dir = vec_norm(rot_any(g_env.scene.cam.dir,
		g_env.scene.cam.right, 9));
		g_env.scene.cam.up = cross_pr(g_env.scene.cam.dir,
		g_env.scene.cam.right);
		g_env.scene.cam.look_at = vec_add(g_env.scene.cam.pos,
		vec_mult(g_env.scene.cam.dir, g_env.scene.cam.dist));
	}
}

void		rotate_cam(int keyval)
{
	if (keyval == 65361)
	{
		g_env.scene.cam.dir = vec_norm(rot_any(g_env.scene.cam.dir,
		g_env.scene.cam.up, -9));
		g_env.scene.cam.look_at = vec_add(g_env.scene.cam.pos,
		vec_mult(g_env.scene.cam.dir, g_env.scene.cam.dist));
	}
	if (keyval == 65363)
	{
		g_env.scene.cam.dir = vec_norm(rot_any(g_env.scene.cam.dir,
		g_env.scene.cam.up, 9));
		g_env.scene.cam.look_at = vec_add(g_env.scene.cam.pos,
		vec_mult(g_env.scene.cam.dir, g_env.scene.cam.dist));
	}
	rotate_cam_bis(keyval);
	if (keyval == 65451)
		g_env.scene.iter_refl++;
	if (keyval == 65453 && g_env.scene.iter_refl > 0)
		g_env.scene.iter_refl--;
}
