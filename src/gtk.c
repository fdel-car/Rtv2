/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 17:08:45 by fdel-car          #+#    #+#             */
/*   Updated: 2016/11/06 19:53:30 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void 	*find_objects(char *name ,unsigned int *n )
{
	t_light *lights;
	t_obj *obj;

	lights = g_env.scene.lgt;
	obj = g_env.scene.obj;
	while (obj)
	{
		if (ft_strcmp(obj->name, name) == 0)
		{
			*n = 1;
			return (obj);
		}
		obj = obj->next;
	}
	while (lights)
	{
		if (ft_strcmp(lights->name, name) == 0)
		{
			*n = 2;
			return (lights);
		}
		lights = lights->next;
	}
	return (NULL);
}

void	save_entry_transformation_light(GtkEntry *entry, t_gtkData *data)
{
	float ret;

	ret = ft_atof(gtk_entry_get_text(entry));
	if(ft_strcmp(data->desc,"posx") == 0)
		((t_light *)data->obj)->pos.x  = ret;
	if(ft_strcmp(data->desc,"posy") == 0)
		((t_light *)data->obj)->pos.y  = ret;
	if(ft_strcmp(data->desc,"posz") == 0)
		((t_light *)data->obj)->pos.z  = ret;
	if(ft_strcmp(data->desc,"rayon") == 0)
		((t_light *)data->obj)->rayon  = ret;
}

void	save_entry_transformation_object(GtkEntry *entry, t_gtkData *data)
{
	float ret;

	ret = ft_atof(gtk_entry_get_text(entry));
	if(ft_strcmp(data->desc,"posx") == 0)
		((t_obj *)data->obj)->pos.x  = ret;
	else if(ft_strcmp(data->desc,"posy") == 0)
		((t_obj *)data->obj)->pos.y  = ret;
	else if(ft_strcmp(data->desc,"posz") == 0)
		((t_obj *)data->obj)->pos.z  = ret;
	else if(ft_strcmp(data->desc,"dirx") == 0)
		((t_obj *)data->obj)->dir.x  = ret;
	else if(ft_strcmp(data->desc,"diry") == 0)
		((t_obj *)data->obj)->dir.y  = ret;
	else if(ft_strcmp(data->desc,"dirz") == 0)
		((t_obj *)data->obj)->dir.z  = ret;
	else if(ft_strcmp(data->desc,"rayon") == 0)
		((t_obj *)data->obj)->rayon  = ret;
}

void	create_transformation_widget_object(void *object, GtkWidget *grid)
{
	GtkWidget *label[3];
	GtkWidget *pos_entry[3];
	GtkWidget *dir_entry[3];
	GtkWidget *rayon_entry;
	GtkEntryBuffer *buffer_pos[3];
	GtkEntryBuffer *buffer_dir[3];
	GtkEntryBuffer *buffer_rayon;
	t_obj *current_obj;
	char *s_entry = NULL;
	t_gtkData *entry_posx = NULL;
	t_gtkData *entry_posy = NULL;
	t_gtkData *entry_posz = NULL;
	t_gtkData *entry_dirx = NULL;
	t_gtkData *entry_diry = NULL;
	t_gtkData *entry_dirz = NULL;
	t_gtkData *entry_rayon = NULL;

	s_entry = malloc(sizeof(char) * 10);
	entry_posx = malloc(sizeof(t_gtkData));
	entry_posy = malloc(sizeof(t_gtkData));
	entry_posz = malloc(sizeof(t_gtkData));
	entry_dirx = malloc(sizeof(t_gtkData));
	entry_diry = malloc(sizeof(t_gtkData));
	entry_dirz = malloc(sizeof(t_gtkData));
	entry_rayon = malloc(sizeof(t_gtkData));
	current_obj = (t_obj *)object;
	sprintf(s_entry,"%f", current_obj->pos.x);
	buffer_pos[0] = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%f", current_obj->pos.y);
	buffer_pos[1] = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%f", current_obj->pos.z);
	buffer_pos[2] = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%f", current_obj->dir.x);
	buffer_dir[0] = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%f", current_obj->dir.y);
	buffer_dir[1] = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%f", current_obj->dir.z);
	buffer_dir[2] = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%f", current_obj->rayon);
	buffer_rayon = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	label[0] = gtk_label_new("Position");
	label[1] = gtk_label_new("Direction");
	label[2] = gtk_label_new("Rayon");
	pos_entry[0] = gtk_entry_new_with_buffer(buffer_pos[0]);
	pos_entry[1] = gtk_entry_new_with_buffer(buffer_pos[1]);
	pos_entry[2] = gtk_entry_new_with_buffer(buffer_pos[2]);
	dir_entry[0] = gtk_entry_new_with_buffer(buffer_dir[0]);
	dir_entry[1] = gtk_entry_new_with_buffer(buffer_dir[1]);
	dir_entry[2] = gtk_entry_new_with_buffer(buffer_dir[2]);
	rayon_entry = gtk_entry_new_with_buffer(buffer_rayon);
	gtk_entry_set_width_chars ((GtkEntry *)pos_entry[0], 6);
	gtk_entry_set_width_chars ((GtkEntry *)pos_entry[1], 6);
	gtk_entry_set_width_chars ((GtkEntry *)pos_entry[2], 6);
	gtk_entry_set_width_chars ((GtkEntry *)dir_entry[0], 6);
	gtk_entry_set_width_chars ((GtkEntry *)dir_entry[1], 6);
	gtk_entry_set_width_chars ((GtkEntry *)dir_entry[2], 6);
	gtk_entry_set_width_chars ((GtkEntry *)rayon_entry, 6);
	gtk_entry_set_max_length ((GtkEntry *)pos_entry[0], 6);
	gtk_entry_set_max_length ((GtkEntry *)pos_entry[1], 6);
	gtk_entry_set_max_length ((GtkEntry *)pos_entry[2], 6);
	gtk_entry_set_max_length ((GtkEntry *)dir_entry[0], 6);
	gtk_entry_set_max_length ((GtkEntry *)dir_entry[1], 6);
	gtk_entry_set_max_length ((GtkEntry *)dir_entry[2], 6);
	gtk_entry_set_max_length ((GtkEntry *)rayon_entry, 6);
	gtk_grid_attach (GTK_GRID (grid), label[0], 0, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), label[1], 0, 1, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), label[2], 0, 2, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), pos_entry[0], 1, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), pos_entry[1], 2, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), pos_entry[2], 3, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), dir_entry[0], 1, 1, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), dir_entry[1], 2, 1, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), dir_entry[2], 3, 1, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), rayon_entry, 1, 2, 1, 1);

	entry_posx->data = pos_entry[0];
	entry_posx->desc = ft_strdup("posx");
	entry_posx->obj = current_obj;

	entry_posy->data = pos_entry[1];
	entry_posy->desc = ft_strdup("posy");
	entry_posy->obj = current_obj;

	entry_posz->data = pos_entry[2];
	entry_posz->desc = ft_strdup("posz");
	entry_posz->obj = current_obj;

	entry_dirx->data = dir_entry[0];
	entry_dirx->desc = ft_strdup("dirx");
	entry_dirx->obj = current_obj;

	entry_diry->data = dir_entry[1];
	entry_diry->desc = ft_strdup("diry");
	entry_diry->obj = current_obj;

	entry_dirz->data = dir_entry[2];
	entry_dirz->desc = ft_strdup("dirz");
	entry_dirz->obj = current_obj;

	entry_rayon->data = rayon_entry;
	entry_rayon->desc = ft_strdup("rayon");
	entry_rayon->obj = current_obj;

	g_signal_connect(pos_entry[0], "changed",
			G_CALLBACK(save_entry_transformation_object), entry_posx);
	g_signal_connect(pos_entry[1], "changed",
			G_CALLBACK(save_entry_transformation_object), entry_posy);
	g_signal_connect(pos_entry[2], "changed",
			G_CALLBACK(save_entry_transformation_object), entry_posz);
	g_signal_connect(dir_entry[0], "changed",
			G_CALLBACK(save_entry_transformation_object), entry_dirx);
	g_signal_connect(dir_entry[1], "changed",
			G_CALLBACK(save_entry_transformation_object), entry_diry);
	g_signal_connect(dir_entry[2], "changed",
			G_CALLBACK(save_entry_transformation_object), entry_dirz);
	g_signal_connect(rayon_entry, "changed",
			G_CALLBACK(save_entry_transformation_object), entry_rayon);
}

void	create_transformation_widget_light(void *object, GtkWidget *grid)
{
	GtkWidget *label[3];
	GtkWidget *pos_entry[3];
	GtkWidget *rayon_entry;
	GtkEntryBuffer *buffer_pos[3];
	GtkEntryBuffer *buffer_rayon;
	t_light *current_light;
	char *s_entry = NULL;
	t_gtkData *entry_posx = NULL;
	t_gtkData *entry_posy = NULL;
	t_gtkData *entry_posz = NULL;
	t_gtkData *entry_rayon = NULL;

	s_entry = malloc(sizeof(char) * 10);
	entry_posx = malloc(sizeof(t_gtkData));
	entry_posy = malloc(sizeof(t_gtkData));
	entry_posz = malloc(sizeof(t_gtkData));
	entry_rayon = malloc(sizeof(t_gtkData));
	current_light = (t_light *)object;
	sprintf(s_entry,"%f", current_light->pos.x);
	buffer_pos[0] = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%f", current_light->pos.y);
	buffer_pos[1] = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%f", current_light->pos.z);
	buffer_pos[2] = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%f", current_light->rayon);
	buffer_rayon = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	label[0] = gtk_label_new("Position");
	label[2] = gtk_label_new("Rayon");
	pos_entry[0] = gtk_entry_new_with_buffer(buffer_pos[0]);
	pos_entry[1] = gtk_entry_new_with_buffer(buffer_pos[1]);
	pos_entry[2] = gtk_entry_new_with_buffer(buffer_pos[2]);
	rayon_entry = gtk_entry_new_with_buffer(buffer_rayon);
	gtk_entry_set_width_chars ((GtkEntry *)pos_entry[0], 6);
	gtk_entry_set_width_chars ((GtkEntry *)pos_entry[1], 6);
	gtk_entry_set_width_chars ((GtkEntry *)pos_entry[2], 6);
	gtk_entry_set_width_chars ((GtkEntry *)rayon_entry, 6);
	gtk_entry_set_max_length ((GtkEntry *)pos_entry[0], 6);
	gtk_entry_set_max_length ((GtkEntry *)pos_entry[1], 6);
	gtk_entry_set_max_length ((GtkEntry *)pos_entry[2], 6);
	gtk_entry_set_max_length ((GtkEntry *)rayon_entry, 6);
	gtk_grid_attach (GTK_GRID (grid), label[0], 0, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), label[2], 0, 1, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), pos_entry[0], 1, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), pos_entry[1], 2, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), pos_entry[2], 3, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), rayon_entry, 1, 1, 1, 1);

	entry_posx->data = pos_entry[0];
	entry_posx->desc = ft_strdup("posx");
	entry_posx->obj = current_light;

	entry_posy->data = pos_entry[1];
	entry_posy->desc = ft_strdup("posy");
	entry_posy->obj = current_light;

	entry_posz->data = pos_entry[2];
	entry_posz->desc = ft_strdup("posz");
	entry_posz->obj = current_light;

	entry_rayon->data = rayon_entry;
	entry_rayon->desc = ft_strdup("rayon");
	entry_rayon->obj = current_light;

	g_signal_connect(pos_entry[0], "changed",
			G_CALLBACK(save_entry_transformation_light), entry_posx);
	g_signal_connect(pos_entry[1], "changed",
			G_CALLBACK(save_entry_transformation_light), entry_posy);
	g_signal_connect(pos_entry[2], "changed",
			G_CALLBACK(save_entry_transformation_light), entry_posz);
	g_signal_connect(rayon_entry, "changed",
			G_CALLBACK(save_entry_transformation_light), entry_rayon);
}

void	create_list_of_attributs(void *objects, unsigned int type)
{
	GtkWidget *grid;
	GList *children, *iter;

	children = gtk_container_get_children(GTK_CONTAINER(gtk_builder_get_object\
				(g_env.build, "right_menu")));
	for(iter = children; iter != NULL; iter = g_list_next(iter))
		gtk_widget_destroy(GTK_WIDGET(iter->data));
	g_list_free(children);
	grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(gtk_builder_get_object(g_env.build,
					"right_menu")), grid);
	if (type == 1)
		create_transformation_widget_object(objects, grid);
	else if (type == 2)
		create_transformation_widget_light(objects, grid);
	gtk_widget_show_all(g_env.win);
}

void 	select_current_obj(GtkTreeView *treeview, GtkTreePath *path)
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

void	create_list_of_objects(void)
{
	t_obj				*obj;
	t_light				*lgt;
	GtkListStore		*model;
	GtkTreeIter			iter;
	GtkCellRenderer		*cell;
	GtkTreeViewColumn	*column;
	GtkWidget			*tree_view;

	obj = g_env.scene.obj;
	lgt = g_env.scene.lgt;
	model = GTK_LIST_STORE(gtk_builder_get_object(g_env.build,"list_object"));
	tree_view = GTK_WIDGET(gtk_builder_get_object(g_env.build,"tree_object"));
	while (obj)
	{
		gtk_list_store_append (GTK_LIST_STORE (model), &iter);
		gtk_list_store_set (GTK_LIST_STORE (model), &iter, 0, obj->name, -1);
		obj = obj->next;
	}
	while (lgt)
	{
		gtk_list_store_append (GTK_LIST_STORE (model), &iter);
		gtk_list_store_set (GTK_LIST_STORE (model), &iter,0, lgt->name, -1);
		lgt = lgt->next;
	}
	cell = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Objects", cell,
			"text", 0, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view),
			GTK_TREE_VIEW_COLUMN(column));
	g_signal_connect(tree_view, "row-activated", (GCallback) select_current_obj,
			NULL);
}
