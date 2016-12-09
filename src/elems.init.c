/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elems.init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 17:39:03 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/09 15:25:03 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_mater		init_mater(void)
{
	t_mater	new;

	new.shiny = 0;
	new.int_refl = 0;
	new.int_trans = 0;
	new.color = color_new(0, 0, 0);
	new.tex = NULL;
	new.ntex = NULL;
	new.ttex = NULL;
	new.ctex = NULL;
	new.indice = 1.0;
	return (new);
}

void		init_gtk_bis(void)
{
	static char *anti_alia[] = {"None", "2x AA", "4x AA", "8x AA", "16x AA"};
	int			iter;

	iter = 0;
	g_env.rowstride = WIDTH * 3;
	g_env.rowstride_prev = WIDTH_PREVIEW * 3;
	g_env.state_prev = FALSE;
	while (iter < 5)
	{
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(g_env.aa_choice),
				anti_alia[iter]);
		iter++;
	}
	init_gtk_create_widget();
	init_gtk_filter_widget();
	set_signal_create_object();
	set_signal_open_save_scene();
	set_signal_switch_cam();
}

void		init_gtk(void)
{
	g_env.build = gtk_builder_new_from_file("ressources/interface.glade");
	g_env.win = GTK_WIDGET(gtk_builder_get_object(g_env.build, "win"));
	g_env.pix = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, WIDTH, HEIGHT);
	g_env.filter = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, WIDTH, HEIGHT);
	g_env.filter_p = gdk_pixbuf_get_pixels(g_env.filter);
	g_env.pix_prev = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8,
			WIDTH_PREVIEW, HEIGHT_PREVIEW);
	g_env.img = GTK_WIDGET(gtk_builder_get_object(g_env.build, "final_img"));
	g_env.prev = GTK_WIDGET(gtk_builder_get_object(g_env.build, "prev_img"));
	g_env.aa_choice = GTK_WIDGET(gtk_builder_get_object(g_env.build,
				"aa_choice"));
	g_env.spin_refl = GTK_WIDGET(gtk_builder_get_object(g_env.build,
				"spin_refl"));
	g_env.toggle_prev = GTK_WIDGET(gtk_builder_get_object(g_env.build,
				"prev_button"));
	g_env.pixels = gdk_pixbuf_get_pixels(g_env.pix);
	g_env.pixels_prev = gdk_pixbuf_get_pixels(g_env.pix_prev);
	init_gtk_bis();
}
