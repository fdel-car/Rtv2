/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/31 14:59:59 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/08 15:45:00 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		desactivate_preview(void)
{
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(g_env.toggle_prev), FALSE);
}

void		switch_state_prev(void)
{
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g_env.toggle_prev)))
	{
		gtk_button_set_label(GTK_BUTTON(g_env.toggle_prev), "Preview ON");
		g_env.state_prev = TRUE;
	}
	else
	{
		gtk_button_set_label(GTK_BUTTON(g_env.toggle_prev), "Preview OFF");
		g_env.state_prev = FALSE;
	}
}

void		save_img(char *filename)
{
	filename = ft_strcat(filename, ".jpeg");
	gdk_pixbuf_save(g_env.pix, filename, "jpeg", NULL,
	"quality", "100", NULL);
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
	if (keyval == 65451)
		g_env.scene.iter_refl++;
	if (keyval == 65453 && g_env.scene.iter_refl > 0)
		g_env.scene.iter_refl--;
}

void		apply_filter(int keyval)
{
	if (keyval == 49)
		sepia_filter();
	if (keyval == 50)
		greyscale_filter();
	if (keyval == 51)
		sobel_filter();
	if (keyval == 96)
		gtk_image_set_from_pixbuf(GTK_IMAGE(g_env.img), g_env.pix);
}

gboolean	key_event(GtkWidget *win, GdkEventKey *event)
{
	if (event->keyval == 65307)
		gtk_main_quit();
	if (g_env.state_prev == FALSE)
		return (FALSE);
	(void)win;
	if (event->keyval == 119)
	{
		g_env.scene.cam.pos = vec_add(g_env.scene.cam.pos, g_env.scene.cam.dir);
		g_env.scene.cam.look_at = vec_add(g_env.scene.cam.look_at,
		g_env.scene.cam.dir);
	}
	if (event->keyval == 115)
	{
		g_env.scene.cam.pos = vec_sub(g_env.scene.cam.pos, g_env.scene.cam.dir);
		g_env.scene.cam.look_at = vec_sub(g_env.scene.cam.look_at,
		g_env.scene.cam.dir);
	}
	if (event->keyval == 97)
	{
		g_env.scene.cam.pos = vec_add(g_env.scene.cam.pos,
		rot_any(g_env.scene.cam.dir, g_env.scene.cam.up, -90));
		g_env.scene.cam.look_at = vec_add(g_env.scene.cam.look_at,
		rot_any(g_env.scene.cam.dir, g_env.scene.cam.up, -90));
	}
	if (event->keyval == 100)
	{
		g_env.scene.cam.pos = vec_add(g_env.scene.cam.pos,
		rot_any(g_env.scene.cam.dir, g_env.scene.cam.up, 90));
		g_env.scene.cam.look_at = vec_add(g_env.scene.cam.look_at,
		rot_any(g_env.scene.cam.dir, g_env.scene.cam.up, 90));
	}
	if (event->keyval == 32)
	{
		g_env.scene.cam.pos = vec_add(g_env.scene.cam.pos,
		rot_any(g_env.scene.cam.dir, g_env.scene.cam.right, -90));
		g_env.scene.cam.look_at = vec_add(g_env.scene.cam.look_at,
		rot_any(g_env.scene.cam.dir, g_env.scene.cam.right, -90));
	}
	if (event->keyval == 99)
	{
		g_env.scene.cam.pos = vec_add(g_env.scene.cam.pos,
		rot_any(g_env.scene.cam.dir, g_env.scene.cam.right, 90));
		g_env.scene.cam.look_at = vec_add(g_env.scene.cam.look_at,
		rot_any(g_env.scene.cam.dir, g_env.scene.cam.right, 90));
	}
	apply_filter(event->keyval);
	rotate_cam(event->keyval);
	g_env.scene.obj->pos = vec_add(g_env.scene.cam.pos,
	vec_mult(g_env.scene.cam.dir, 2));
	launch_preview();
	return (TRUE);
}
