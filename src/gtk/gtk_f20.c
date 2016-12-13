/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_f20.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 18:46:26 by slgracie          #+#    #+#             */
/*   Updated: 2016/12/13 19:08:24 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	create_list_of_attributs2(void *objects, unsigned int type,
		GtkWidget *grid_material, GtkWidget *grid_transformation)
{
	if (type == 1)
	{
		create_transformation_widget_object(objects, grid_transformation);
		create_material_widget_object(objects, grid_material);
	}
	else if (type == 2)
	{
		create_transformation_widget_light(objects, grid_transformation);
		create_material_widget_light(objects, grid_material);
	}
	gtk_widget_show_all(g_env.win);
}

void	create_list_of_attributs(void *objects, unsigned int type)
{
	GtkWidget	*grid_transformation;
	GtkWidget	*grid_material;
	GList		*children;
	GList		*iter;

	children = gtk_container_get_children(GTK_CONTAINER(
				gtk_builder_get_object(g_env.build, "right_menu")));
	iter = children;
	while (iter != NULL)
	{
		gtk_widget_destroy(GTK_WIDGET(iter->data));
		iter = g_list_next(iter);
	}
	g_list_free(children);
	grid_transformation = gtk_grid_new();
	grid_material = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(gtk_builder_get_object(g_env.build,
					"right_menu")), grid_transformation);
	gtk_container_add(GTK_CONTAINER(gtk_builder_get_object(g_env.build,
					"right_menu")), grid_material);
	create_list_of_attributs2(objects, type,
			grid_transformation, grid_material);
}

void	select_current_obj(GtkTreeView *treeview, GtkTreePath *path)
{
	GtkTreeModel	*model;
	GtkTreeIter		iter;
	void			*found_obj;
	unsigned int	n;
	gchar			*name;

	n = 0;
	found_obj = NULL;
	model = gtk_tree_view_get_model(treeview);
	if (gtk_tree_model_get_iter(model, &iter, path))
	{
		gtk_tree_model_get(model, &iter, 0, &name, -1);
		found_obj = find_objects(name, &n);
		g_free(name);
		if (n != 0)
			create_list_of_attributs(found_obj, n);
	}
}

void	view_popup_menu_delete_row2(GtkTreeModel *model,
		GtkTreeIter iter, GtkTreePath *path)
{
	gchar			*name;
	void			*found_obj;
	unsigned int	n;

	n = 0;
	found_obj = NULL;
	gtk_tree_model_get(model, &iter, 0, &name, -1);
	found_obj = find_objects(name, &n);
	g_free(name);
	if (n != 0)
	{
		delete_objects(found_obj, n);
		gtk_tree_path_free(path);
		create_list_of_objects();
		launch_preview();
		launch_thread();
	}
}

void	view_popup_menu_delete_row(GtkWidget *menuitem, gpointer userdata)
{
	GtkTreeModel	*model;
	GtkTreeView		*treeview;
	GtkTreeIter		iter;
	GtkTreePath		*path;

	path = NULL;
	model = NULL;
	treeview = NULL;
	(void)menuitem;
	treeview = GTK_TREE_VIEW(gtk_builder_get_object(
				g_env.build, "tree_object"));
	model = gtk_tree_view_get_model(treeview);
	path = (GtkTreePath *)userdata;
	if (gtk_tree_model_get_iter(model, &iter, path))
		view_popup_menu_delete_row2(model, iter, path);
}
