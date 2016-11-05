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

void		switch_key_focus(void)
{
	ft_putstr("lol");
}

void		save_img(int keyval)
{
	if (keyval == 65421)
		gdk_pixbuf_save (g_env.pix, "saves/rtv2.jpeg", "jpeg", NULL,
		"quality", "100", NULL);
}

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
	if (keyval == 65451)
		g_env.scene.iter_refl++;
	if (keyval == 65453 && g_env.scene.iter_refl > 0)
		g_env.scene.iter_refl--;
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
	save_img(event->keyval);
	launch_preview();
	if (event->keyval == 65293)
		launch_thread();
	return (TRUE);
}
