/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_f2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 19:10:24 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/13 19:11:20 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	check_filter(void)
{
	char	*s;

	s = gtk_combo_box_text_get_active_text(
	GTK_COMBO_BOX_TEXT(gtk_builder_get_object(g_env.build, "filtre_combo")));
	if (!s)
		return ;
	if (ft_strcmp("Sepia", s) == 0)
		sepia_filter();
	else if (ft_strcmp("Cartoon", s) == 0)
		sobel_filter();
	else if (ft_strcmp("Greyscale", s) == 0)
		greyscale_filter();
	free(s);
}

void	switch_1(char *s)
{
	if (ft_strcmp("Cartoon", s) == 0)
	{
		g_env.oculus = FALSE;
		g_env.oculus_left = FALSE;
		g_env.width = 1280;
		g_env.scene.cam.view_w = 2.4;
		g_env.scene.cam.x_ind = g_env.scene.cam.view_w / (float)WIDTH;
		init_limits();
		sobel_filter();
	}
	if (ft_strcmp("Greyscale", s) == 0)
	{
		g_env.oculus = FALSE;
		g_env.oculus_left = FALSE;
		g_env.width = 1280;
		g_env.scene.cam.view_w = 2.4;
		g_env.scene.cam.x_ind = g_env.scene.cam.view_w / (float)WIDTH;
		init_limits();
		greyscale_filter();
	}
}

void	switch_2(char *s)
{
	if (ft_strcmp("Stereocopique", s) == 0)
	{
		g_env.stereo = TRUE;
		g_env.stereo_red = TRUE;
		g_env.oculus = FALSE;
		g_env.oculus_left = FALSE;
		g_env.width = 1280;
		g_env.scene.cam.view_w = 2.4;
		g_env.scene.cam.x_ind = g_env.scene.cam.view_w / (float)WIDTH;
		init_limits();
	}
	if (ft_strcmp("Oculus", s) == 0)
	{
		g_env.stereo = FALSE;
		g_env.stereo_red = FALSE;
		g_env.oculus = TRUE;
		g_env.oculus_left = TRUE;
		g_env.width = 640;
		g_env.scene.cam.view_w = g_env.scene.cam.view_w / 2;
		g_env.scene.cam.x_ind = g_env.scene.cam.view_w / (float)WIDTH;
		init_limits();
	}
}

void	switch_3(char *s)
{
	if (ft_strcmp("None", s) == 0)
	{
		g_env.oculus = FALSE;
		g_env.oculus_left = FALSE;
		g_env.width = 1280;
		g_env.scene.cam.view_w = 2.4;
		g_env.scene.cam.x_ind = g_env.scene.cam.view_w / (float)WIDTH;
		init_limits();
		g_env.stereo = FALSE;
		g_env.oculus = FALSE;
		gtk_image_set_from_pixbuf(GTK_IMAGE(g_env.img), g_env.pix);
	}
}

void	switch_filter(GtkWidget *combo)
{
	char	*s;

	s = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo));
	if (ft_strcmp("Sepia", s) == 0)
	{
		g_env.oculus = FALSE;
		g_env.oculus_left = FALSE;
		g_env.width = 1280;
		g_env.scene.cam.view_w = 2.4;
		g_env.scene.cam.x_ind = g_env.scene.cam.view_w / (float)WIDTH;
		init_limits();
		sepia_filter();
	}
	switch_1(s);
	switch_2(s);
	switch_3(s);
	free(s);
	launch_thread();
}
