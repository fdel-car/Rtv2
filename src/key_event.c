/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/31 14:59:59 by fdel-car          #+#    #+#             */
/*   Updated: 2016/10/31 15:00:00 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		rotate_cam(int keyval)
{
	if (keyval == 65361)
		g_env.scene.cam.dir = vec_norm(rot_any(g_env.scene.cam.dir,
		g_env.scene.cam.up, -9));
	if (keyval == 65363)
		g_env.scene.cam.dir = vec_norm(rot_any(g_env.scene.cam.dir,
		g_env.scene.cam.up, 9));
	if (keyval == 65362)
	{
		g_env.scene.cam.dir = vec_norm(rot_any(g_env.scene.cam.dir,
		g_env.scene.cam.right, -9));
		g_env.scene.cam.up = cross_pr(g_env.scene.cam.dir,
		g_env.scene.cam.right);
	}
	if (keyval == 65364)
	{
		g_env.scene.cam.dir = vec_norm(rot_any(g_env.scene.cam.dir,
		g_env.scene.cam.right, 9));
		g_env.scene.cam.up = cross_pr(g_env.scene.cam.dir,
		g_env.scene.cam.right);
	}
}

gboolean	key_event(GtkWidget *win, GdkEventKey *event)
{
	(void)win;
	if (event->keyval == 119)
		g_env.scene.cam.pos = vec_add(g_env.scene.cam.pos, g_env.scene.cam.dir);
	if (event->keyval == 115)
		g_env.scene.cam.pos = vec_sub(g_env.scene.cam.pos, g_env.scene.cam.dir);
	if (event->keyval == 97)
		g_env.scene.cam.pos = vec_add(g_env.scene.cam.pos,
		rot_any(g_env.scene.cam.dir, g_env.scene.cam.up, -90));
	if (event->keyval == 100)
		g_env.scene.cam.pos = vec_add(g_env.scene.cam.pos,
		rot_any(g_env.scene.cam.dir, g_env.scene.cam.up, 90));
	if (event->keyval == 32)
		g_env.scene.cam.pos = vec_add(g_env.scene.cam.pos,
		rot_any(g_env.scene.cam.dir, g_env.scene.cam.right, -90));
	if (event->keyval == 99)
		g_env.scene.cam.pos = vec_add(g_env.scene.cam.pos,
		rot_any(g_env.scene.cam.dir, g_env.scene.cam.right, 90));
	rotate_cam(event->keyval);
	launch_thread();
	return (TRUE);
}
