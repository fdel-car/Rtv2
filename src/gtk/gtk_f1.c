/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_f1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 18:55:22 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/13 19:04:23 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	open_file(char *filename)
{
	if (ft_strcmp(".scn", filename + ft_strlen(filename) - 4) == 0)
	{
		free_objects(FALSE);
		free_lights();
		load_file(filename);
		create_list_of_objects();
		launch_thread();
		launch_preview();
	}
}

void	switch_cam_pos(void)
{
	if (g_env.scene.cam.c_pos == 1)
	{
		g_env.scene.cam.pos = g_env.scene.cam.pos1;
		g_env.scene.cam.look_at = vec_add(g_env.scene.cam.pos,
		vec_mult(g_env.scene.cam.dir, g_env.scene.cam.dist));
	}
	else if (g_env.scene.cam.c_pos == 2)
	{
		g_env.scene.cam.pos = g_env.scene.cam.pos2;
		g_env.scene.cam.look_at = vec_add(g_env.scene.cam.pos,
		vec_mult(g_env.scene.cam.dir, g_env.scene.cam.dist));
	}
	else if (g_env.scene.cam.c_pos == 3)
	{
		g_env.scene.cam.pos = g_env.scene.cam.pos3;
		g_env.scene.cam.look_at = vec_add(g_env.scene.cam.pos,
		vec_mult(g_env.scene.cam.dir, g_env.scene.cam.dist));
	}
}

void	save_image_chooser(void)
{
	GtkWidget				*dialog;
	GtkFileChooser			*chooser;
	GtkFileChooserAction	action;
	gint					res;
	char					*filename;

	filename = 0;
	action = GTK_FILE_CHOOSER_ACTION_SAVE;
	dialog = gtk_file_chooser_dialog_new("Save File", GTK_WINDOW(g_env.win),
	action, "_Cancel", GTK_RESPONSE_CANCEL, "_Save", GTK_RESPONSE_ACCEPT, NULL);
	chooser = GTK_FILE_CHOOSER(dialog);
	gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);
	gtk_file_chooser_set_current_name(chooser, ("Untitled document"));
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		filename = gtk_file_chooser_get_filename(chooser);
		save_img(filename);
		g_free(filename);
	}
	gtk_widget_destroy(dialog);
}

void	switch_cam(GtkWidget *entry)
{
	if (entry == GTK_WIDGET(gtk_builder_get_object(g_env.build, "cam_prev")))
	{
		if (g_env.scene.cam.c_pos == 1)
			g_env.scene.cam.c_pos = 3;
		else if (g_env.scene.cam.c_pos == 2)
			g_env.scene.cam.c_pos = 1;
		else if (g_env.scene.cam.c_pos == 3)
			g_env.scene.cam.c_pos = 2;
	}
	else if (entry == GTK_WIDGET(gtk_builder_get_object(g_env.build,
		"cam_next")))
	{
		if (g_env.scene.cam.c_pos == 1)
			g_env.scene.cam.c_pos = 2;
		else if (g_env.scene.cam.c_pos == 2)
			g_env.scene.cam.c_pos = 3;
		else if (g_env.scene.cam.c_pos == 3)
			g_env.scene.cam.c_pos = 1;
	}
	switch_cam_pos();
	launch_preview();
	launch_thread();
}

void	open_scene(void)
{
	GtkWidget				*dialog;
	GtkFileChooserAction	action;
	gint					res;
	char					*filename;
	GtkFileChooser			*chooser;

	filename = 0;
	action = GTK_FILE_CHOOSER_ACTION_OPEN;
	dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(g_env.win),
	action, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		chooser = GTK_FILE_CHOOSER(dialog);
		filename = gtk_file_chooser_get_filename(chooser);
		open_file(filename);
		g_free(filename);
	}
	gtk_widget_destroy(dialog);
}
