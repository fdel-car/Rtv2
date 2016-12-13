#include "rt.h"

void	create_list_of_attributs(void *objects, unsigned int type)
{
	GtkWidget *grid_transformation;
	GtkWidget *grid_material;
	GList *children, *iter;

	children = gtk_container_get_children(GTK_CONTAINER(gtk_builder_get_object\
		(g_env.build, "right_menu")));
	for(iter = children; iter != NULL; iter = g_list_next(iter))
		gtk_widget_destroy(GTK_WIDGET(iter->data));
	g_list_free(children);
	grid_transformation = gtk_grid_new();
	grid_material = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(gtk_builder_get_object(g_env.build,
					"right_menu")), grid_transformation);
	gtk_container_add(GTK_CONTAINER(gtk_builder_get_object(g_env.build,
					"right_menu")), grid_material);
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

void	select_current_obj(GtkTreeView *treeview, GtkTreePath *path)
{
	GtkTreeModel 	*model;
	GtkTreeIter  	iter;
	void			*found_obj = NULL;
	unsigned int 	n = 0;

	model = gtk_tree_view_get_model(treeview);
	if (gtk_tree_model_get_iter(model, &iter, path))
	{
		gchar *name;
		gtk_tree_model_get(model, &iter, 0, &name, -1);
		found_obj = find_objects(name, &n);
		g_free(name);
		if (n != 0)
			create_list_of_attributs(found_obj, n);
	}
}

void	view_popup_menu_delete_row(GtkWidget *menuitem, gpointer userdata)
{
	GtkTreeModel 	*model = NULL;
	GtkTreeView *treeview = NULL;
	GtkTreeIter  	iter;
	GtkTreePath *path = NULL;
	void			*found_obj = NULL;
	unsigned int 	n = 0;
	(void)menuitem;
	treeview = GTK_TREE_VIEW(gtk_builder_get_object(g_env.build,"tree_object"));
	model = gtk_tree_view_get_model(treeview);
	path = (GtkTreePath *)userdata;
	if (gtk_tree_model_get_iter(model, &iter, path))
	{
		gchar *name;
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
}
