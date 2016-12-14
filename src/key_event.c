/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/31 14:59:59 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/14 13:22:56 by fdel-car         ###   ########.fr       */
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
	{
		free_exit();
		return (FALSE);
	}
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
	move_cam(event->keyval);
	apply_filter(event->keyval);
	rotate_cam(event->keyval);
	launch_preview();
	return (TRUE);
}
