#include "rt.h"

void save_entry_transformation_object(GtkEntry *entry, t_gtkData *data){

	float ret;

	//change value of attribut of object
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

	printf("ret =% f\n", ret);

}


void 	*find_objects(char *name ,unsigned int *n ){

	t_light *lights;
	t_obj *obj;

	lights = g_env.scene.lgt;
	obj = g_env.scene.obj;
	while (obj)
	{
		// if light n = 2 obj = 1
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

void create_widget_attribute(void *object){

printf("1\n");
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

printf("2\n");

	s_entry = malloc(sizeof(char) * 10);
    
    entry_posx = malloc(sizeof(t_gtkData));
    entry_posy = malloc(sizeof(t_gtkData));
    entry_posz = malloc(sizeof(t_gtkData));

    entry_dirx = malloc(sizeof(t_gtkData));
    entry_diry = malloc(sizeof(t_gtkData));
    entry_dirz = malloc(sizeof(t_gtkData));
    
    entry_rayon = malloc(sizeof(t_gtkData));
printf("3\n");

	current_obj = (t_obj *)object;
	//set buffer with value of objects
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
printf("4\n");
   	

	//init entry with buffers
	pos_entry[0] = GTK_WIDGET(gtk_builder_get_object(g_env.build, "Entry_posx"));
	printf("40\n");

	pos_entry[1] = GTK_WIDGET(gtk_builder_get_object(g_env.build, "Entry_posy"));
printf("41\n");

	pos_entry[2] = GTK_WIDGET(gtk_builder_get_object(g_env.build, "Entry_posz"));
printf("42\n");

	dir_entry[0] = GTK_WIDGET(gtk_builder_get_object(g_env.build, "Entry_dirx"));
	dir_entry[1] = GTK_WIDGET(gtk_builder_get_object(g_env.build, "Entry_diry"));
	dir_entry[2] = GTK_WIDGET(gtk_builder_get_object(g_env.build, "Entry_dirz"));

	rayon_entry = GTK_WIDGET(gtk_builder_get_object(g_env.build, "Entry_rayon"));
printf("45\n");

	gtk_entry_set_buffer (GTK_ENTRY(pos_entry[0]),buffer_pos[0]);
	gtk_entry_set_buffer (GTK_ENTRY(pos_entry[1]),buffer_pos[1]);
	gtk_entry_set_buffer (GTK_ENTRY(pos_entry[2]),buffer_pos[2]);

	gtk_entry_set_buffer (GTK_ENTRY(dir_entry[0]),buffer_dir[0]);
	gtk_entry_set_buffer (GTK_ENTRY(dir_entry[1]),buffer_dir[1]);
	gtk_entry_set_buffer (GTK_ENTRY(dir_entry[2]),buffer_dir[2]);

	gtk_entry_set_buffer (GTK_ENTRY(rayon_entry),buffer_rayon);
printf("5\n");

		//set data object to pass to signal handler
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


	//signal handler
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
	printf("6\n");
}


void 	select_current_obj (GtkTreeView        *treeview,
                       GtkTreePath        *path)
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
       //find object in lists of objects
       found_obj = find_objects(name, &n);
       g_free(name);
       // create widget attribut
       //if (n != 0)
       		create_widget_attribute(found_obj);

    }
  }

void create_list_of_objects(){


	t_obj *obj;
	t_light *lgt;
	GtkListStore *model;
	GtkTreeIter iter;
    GtkCellRenderer *cell;
    GtkTreeViewColumn *column;
    GtkWidget *tree_view;

	obj = g_env.scene.obj;
	lgt = g_env.scene.lgt;
	if (!(model = GTK_LIST_STORE(gtk_builder_get_object(g_env.build,"list_object"))))
		printf("list store doesnt find\n");
	if (!(tree_view = GTK_WIDGET(gtk_builder_get_object(g_env.build,"tree_object"))))
		printf("tree view doesnt find\n");

	while (obj)
	{
		gchar *name_o = ft_strdup(obj->name);
    	obj = obj->next;
    	gtk_list_store_append (GTK_LIST_STORE (model), &iter);
        gtk_list_store_set (GTK_LIST_STORE (model), &iter, 0, name_o, 1);
		g_free (name_o);
    }
    while (lgt){
    	gchar *name_o = ft_strdup(lgt->name);
    	lgt = lgt->next;
    	gtk_list_store_append (GTK_LIST_STORE (model), &iter);
        gtk_list_store_set (GTK_LIST_STORE (model), &iter,0, name_o, -1);
		g_free (name_o);
    }
   
    cell = gtk_cell_renderer_text_new ();

    column = gtk_tree_view_column_new_with_attributes ("Objects", cell, "text", 0, NULL);
    gtk_tree_view_append_column (GTK_TREE_VIEW (tree_view), GTK_TREE_VIEW_COLUMN (column));

	g_signal_connect(tree_view, "row-activated", (GCallback) select_current_obj, NULL);


}