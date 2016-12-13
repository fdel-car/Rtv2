/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_f21.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <slgracie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 18:19:07 by slgracie          #+#    #+#             */
/*   Updated: 2016/12/13 19:50:39 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		view_popup_menu(GtkWidget *treeview, GdkEventButton *event,
		GtkTreePath *path, gpointer userdata)
{
	GtkWidget	*menu;
	GtkWidget	*menuitem;

	menu = gtk_menu_new();
	(void)userdata;
	(void)treeview;
	menuitem = gtk_menu_item_new_with_label("Delete");
	g_signal_connect(menuitem, "activate",
			(GCallback)view_popup_menu_delete_row, path);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuitem);
	gtk_widget_show_all(menu);
	gtk_menu_popup_at_pointer(GTK_MENU(menu), (GdkEvent*)event);
}

gboolean	view_onbuttonpressed(GtkWidget *treeview,
		GdkEventButton *event, gpointer userdata)
{
	GtkTreePath			*path;
	GtkTreeSelection	*selection;

	path = NULL;
	if (event->type == GDK_BUTTON_PRESS && event->button == 3)
	{
		if (1)
		{
			selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
			if (gtk_tree_selection_count_selected_rows(selection) <= 1)
			{
				if (gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(treeview),
							(gint)event->x,
							(gint)event->y, &path, NULL, NULL, NULL))
				{
					gtk_tree_selection_unselect_all(selection);
					gtk_tree_selection_select_path(selection, path);
				}
			}
		}
		view_popup_menu(treeview, event, path, userdata);
		return (TRUE);
	}
	return (FALSE);
}
