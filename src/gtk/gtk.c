/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 18:34:15 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/14 12:49:12 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	hide_window(void)
{
	gtk_widget_hide(GTK_WIDGET(gtk_builder_get_object(g_env.build,
	"popup_create_object")));
}

void	create_list_of_objects2(GtkWidget *tree_view)
{
	GtkCellRenderer		*cell;
	static int			i = 0;
	GtkTreeViewColumn	*column;

	cell = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Objects", cell,
			"text", 0, NULL);
	if (i == 0)
	{
		gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view),
				GTK_TREE_VIEW_COLUMN(column));
		i++;
	}
	g_signal_connect(tree_view, "row-activated",
	(GCallback)select_current_obj, NULL);
	g_signal_connect(tree_view, "button-press-event",
	(GCallback)view_onbuttonpressed, NULL);
}

void	create_list_of_objects1(t_obj *obj, t_light *lgt, GtkListStore *model)
{
	GtkTreeIter			iter;

	while (obj)
	{
		if (obj->type != OCULUS)
		{
			gtk_list_store_append(GTK_LIST_STORE(model), &iter);
			gtk_list_store_set(GTK_LIST_STORE(model), &iter, 0, obj->name, -1);
		}
		obj = obj->next;
	}
	while (lgt)
	{
		gtk_list_store_append(GTK_LIST_STORE(model), &iter);
		gtk_list_store_set(GTK_LIST_STORE(model), &iter, 0, lgt->name, -1);
		lgt = lgt->next;
	}
}

void	create_list_of_objects(void)
{
	t_obj				*obj;
	t_light				*lgt;
	GtkListStore		*model;
	GtkWidget			*tree_view;

	obj = g_env.scene.obj;
	lgt = g_env.scene.lgt;
	model = GTK_LIST_STORE(gtk_builder_get_object(g_env.build, "list_object"));
	tree_view = GTK_WIDGET(gtk_builder_get_object(g_env.build, "tree_object"));
	gtk_list_store_clear(model);
	create_list_of_objects1(obj, lgt, model);
	create_list_of_objects2(tree_view);
}
