/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 17:08:45 by fdel-car          #+#    #+#             */
/*   Updated: 2016/11/19 18:35:03 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void open_file(char *filename){
	printf("%s\n",filename );
	printf("%s\n",filename + ft_strlen(filename ) -4 );
	if (ft_strcmp(".scn", filename + ft_strlen(filename) - 4) == 0)
	{
		load_file(filename);
		create_list_of_objects();
		launch_thread();
		launch_preview();
	}
}
void save_scene(void){

}

void switch_cam_pos(){
	if (g_env.scene.cam.c_pos == 1)
		g_env.scene.cam.pos = g_env.scene.cam.pos1;
	else if (g_env.scene.cam.c_pos == 2)
		g_env.scene.cam.pos = g_env.scene.cam.pos2;
	else if (g_env.scene.cam.c_pos == 3)
		g_env.scene.cam.pos = g_env.scene.cam.pos3;
}

void switch_cam(GtkWidget *entry){
	if (entry == GTK_WIDGET(gtk_builder_get_object(g_env.build, "cam_prev")))
	{
		if (g_env.scene.cam.c_pos == 1)
			g_env.scene.cam.c_pos = 3;
		else if (g_env.scene.cam.c_pos == 2)
			g_env.scene.cam.c_pos = 1;
		else if (g_env.scene.cam.c_pos == 3)
			g_env.scene.cam.c_pos = 2;
	}
	else if (entry == GTK_WIDGET(gtk_builder_get_object(g_env.build, "cam_next")))
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

void open_scene(){
	GtkWidget *dialog;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	gint res;

	dialog = gtk_file_chooser_dialog_new ("Open File",GTK_WINDOW(g_env.win),action,"_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT,NULL);
	//gtk_dialog_add_button(GTK_DIALOG(dialog),"_Cancel", GTK_RESPONSE_CANCEL);
	//gtk_dialog_add_button(GTK_DIALOG(dialog),"_Open", GTK_RESPONSE_ACCEPT);

	res = gtk_dialog_run (GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	  {
	    char *filename;
	    GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
	    filename = gtk_file_chooser_get_filename (chooser);
	    open_file (filename);
	    g_free (filename);
  }

gtk_widget_destroy (dialog);
}

void init_gtk_create_widget(void)
{
	GtkWidget *combo;
	static char *combo_text[] = {"Sphere", "Plan", "Cone", "Cylindre"};
	int		i;

	i = 0;
	combo = GTK_WIDGET(gtk_builder_get_object(g_env.build,"create_type"));
	while (i < 4)
	{
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo),
				combo_text[i]);
		i++;
	}
}

t_obj *add_object_type(char *s, t_obj *obj)
{
	if (ft_strcmp("Sphere",s) == 0)
		obj->type = SPHERE;
	else if (ft_strcmp("Plan",s) == 0)
		obj->type = PLANE;
	else if (ft_strcmp("Cone",s) == 0)
		obj->type = CONE;
	else if (ft_strcmp("Cylindre",s) == 0)
		obj->type = CYLINDER;
	return (obj);
}

t_obj *add_object_name(t_obj *obj)
{
	GtkEntry *name;

	name = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_name"));
	obj->name = ft_strdup(gtk_entry_get_text(name));

	return (obj);
}

t_obj *add_object_pos(t_obj *obj)
{
	GtkEntry *posx;
	GtkEntry *posy;
	GtkEntry *posz;

	posx = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_posx"));
	posy = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_posy"));
	posz = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_posz"));

	obj->pos.x = ft_atof(gtk_entry_get_text(posx));
	obj->pos.y = ft_atof(gtk_entry_get_text(posy));
	obj->pos.z = ft_atof(gtk_entry_get_text(posz));

	return (obj);
}

t_obj *add_object_dir(t_obj *obj)
{
	GtkEntry *dirx;
	GtkEntry *diry;
	GtkEntry *dirz;

	dirx = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_dirx"));
	diry = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_diry"));
	dirz = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_dirz"));

	obj->dir.x = ft_atof(gtk_entry_get_text(dirx));
	obj->dir.y = ft_atof(gtk_entry_get_text(diry));
	obj->dir.z = ft_atof(gtk_entry_get_text(dirz));
	obj->dir = vec_norm(obj->dir);

	return (obj);
}

t_obj *add_object_norm(t_obj *obj)
{
	GtkEntry *normx;
	GtkEntry *normy;
	GtkEntry *normz;

	normx = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_normx"));
	normy = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_normy"));
	normz = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_normz"));

	obj->norm.x = ft_atof(gtk_entry_get_text(normx));
	obj->norm.y = ft_atof(gtk_entry_get_text(normy));
	obj->norm.z = ft_atof(gtk_entry_get_text(normz));
	obj->norm = vec_norm(obj->norm);

	return (obj);
}

t_obj *add_object_rayon(t_obj *obj)
{
	GtkEntry *rayon;

	rayon = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_rayon"));
	obj->rayon = ft_atof(gtk_entry_get_text(rayon));

	return (obj);
}

t_obj *add_object_alpha(t_obj *obj)
{
	GtkEntry *alpha;

	alpha = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_angle"));
	obj->alpha = ft_atof(gtk_entry_get_text(alpha)) * M_PI / 180;

	return (obj);
}

t_obj *add_object_mater_shiny(t_obj *obj)
{
	GtkEntry *shiny;

	shiny = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_shiny"));
	obj->mater.shiny = ft_atof(gtk_entry_get_text(shiny));
	return (obj);
}

t_obj *add_object_mater_refl(t_obj *obj)
{
	GtkEntry *refl;

	refl = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_refl"));
	obj->mater.int_refl = ft_atof(gtk_entry_get_text(refl));
	return (obj);
}

t_obj *add_object_mater_trans(t_obj *obj)
{
	GtkEntry *trans;

	trans = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_trans"));
	obj->mater.int_trans = ft_atof(gtk_entry_get_text(trans));
	return (obj);
}

t_obj *add_object_mater_color(t_obj *obj)
{
	GdkRGBA *col;
	GtkColorChooser *e;

	col = malloc(sizeof(GdkRGBA));
	e = GTK_COLOR_CHOOSER(gtk_builder_get_object(g_env.build,"e_color"));
	gtk_color_chooser_get_rgba (e,col);
	obj->mater.color.r  = (int)(col->red * 255);
	obj->mater.color.g  = (int)(col->green * 255);
	obj->mater.color.b  = (int)(col->blue * 255);
	gdk_rgba_free(col);

	return (obj);
}

void clear_entry_1(){
	GtkEntry *name;
	GtkEntry *posx;
	GtkEntry *posy;
	GtkEntry *posz;

	name = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_name"));
	posx = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_posx"));
	posy = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_posy"));
	posz = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_posz"));

	gtk_entry_set_text (name,"");
	gtk_entry_set_text (posx,"");
	gtk_entry_set_text (posy,"");
	gtk_entry_set_text (posz,"");
}

void clear_entry_2(){
	GtkEntry *dirx;
	GtkEntry *diry;
	GtkEntry *dirz;
	GtkEntry *rayon;

	rayon = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_rayon"));
	dirx = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_dirx"));
	diry = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_diry"));
	dirz = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_dirz"));

	gtk_entry_set_text (rayon,"");
	gtk_entry_set_text (dirx,"");
	gtk_entry_set_text (diry,"");
	gtk_entry_set_text (dirz,"");
}

void clear_entry_3(){
	GtkEntry *normx;
	GtkEntry *normy;
	GtkEntry *normz;
	GtkEntry *alpha;

	alpha = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_angle"));
	normx = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_normx"));
	normy = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_normy"));
	normz = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_normz"));

	gtk_entry_set_text (normx,"");
	gtk_entry_set_text (normy,"");
	gtk_entry_set_text (normz,"");
	gtk_entry_set_text (alpha,"");
}

void clear_entry_4(){
	GtkEntry *shiny;
	GtkEntry *refl;
	GtkEntry *trans;

	trans = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_trans"));
	refl = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_refl"));
	shiny = GTK_ENTRY(gtk_builder_get_object(g_env.build,"e_shiny"));

	gtk_entry_set_text (shiny,"");
	gtk_entry_set_text (refl,"");
	gtk_entry_set_text (trans,"");
}

void clear_entry_widget_add_object(void){
	clear_entry_1();
	clear_entry_2();
	clear_entry_3();
	clear_entry_4();
}

void init_obj(t_obj *obj){
	obj->name = NULL;
	obj->src = NULL;
	obj->lst = NULL;
	obj->next = NULL;
	obj->mater.tex = NULL;
	obj->mater.ntex = NULL;

}
void signal_add_object(void)
{
	char *s = NULL;
	t_obj *obj = NULL;

	s = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(gtk_builder_get_object(g_env.build,"create_type")));
	obj = malloc(sizeof(t_obj));
	init_obj(obj);
	add_object_type(s,obj);

	obj = add_object_name(obj);
	obj = add_object_pos(obj);
	obj = add_object_dir(obj);
	obj = add_object_norm(obj);
	obj = add_object_rayon(obj);

	obj = add_object_alpha(obj);
	obj = add_object_mater_shiny(obj);
	obj = add_object_mater_refl(obj);
	obj = add_object_mater_trans(obj);
	obj = add_object_mater_color(obj);
	obj->next = NULL;
	obj->mater.tex = NULL;

	set_func(obj);
	push_obj(obj);
	clear_entry_widget_add_object();
	gtk_widget_hide (GTK_WIDGET(gtk_builder_get_object(g_env.build,"popup_create_object")));
	create_list_of_objects();
	launch_preview();
	launch_thread();
}

void    delete_objects(void *obj, unsigned int n)
{
	t_obj *list_obj;
	t_obj *current_obj;
	t_light *current_light;
	t_light *list_lgt;
	list_obj = g_env.scene.obj;
	list_lgt = g_env.scene.lgt;
	if (n == 1)
	{
		current_obj = (t_obj *)obj;
		if (list_obj == current_obj)
		{
			g_env.scene.obj = list_obj->next;
			free(current_obj->name);
			free(current_obj);
		}
		else
		{
			while (list_obj)
			{
				if (list_obj->next == current_obj)
				{
					list_obj->next = current_obj->next;
					free(current_obj->name);
					free(current_obj);
				}
				list_obj = list_obj->next;
			}
		}
	}
	else if (n == 2)
	{
		current_light = (t_light *)obj;
		if (list_lgt == current_light)
		{
			g_env.scene.lgt = list_lgt->next;
			free(current_light->name);
			free(current_light);
		}
		else
		{
			while (list_lgt)
			{
				if (list_lgt->next == current_light)
				{
					list_lgt->next = current_light->next;
					free(current_light->name);
					free(current_light);
				}
				list_lgt = list_lgt->next;
			}
		}
	}
}

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

void create_object(GtkWidget *entry, t_gtkData *e){
	(void )entry;
	gtk_window_present( GTK_WINDOW(e->data));
}

void    save_color_material_light(GtkEntry *entry, t_gtkData *data)
{
	GdkRGBA *col;

	col = malloc(sizeof(GdkRGBA));
	gtk_color_chooser_get_rgba ((GtkColorChooser *)entry,col);
	if(ft_strcmp(data->desc,"color") == 0)
	{
		((t_light *)data->obj)->color.r  = (int)(col->red * 255);
		((t_light *)data->obj)->color.g  = (int)(col->green * 255);
		((t_light *)data->obj)->color.b  = (int)(col->blue * 255);
	}
	gdk_rgba_free(col);
}

void    save_color_material(GtkEntry *entry, t_gtkData *data)
{
	GdkRGBA *col;

	col = malloc(sizeof(GdkRGBA));
	gtk_color_chooser_get_rgba ((GtkColorChooser *)entry,col);
	if(ft_strcmp(data->desc,"color") == 0)
	{
		((t_obj *)data->obj)->mater.color.r  = (int)(col->red * 255);
		((t_obj *)data->obj)->mater.color.g  = (int)(col->green * 255);
		((t_obj *)data->obj)->mater.color.b  = (int)(col->blue * 255);
	}
	gdk_rgba_free(col);
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

void save_translation_mesh_object(GtkEntry *entry, t_gtkData *data, t_vect oldpos)
{
	t_obj *list;
	float ret;

	list = ((t_obj *)data->obj)->lst;
	ret = ft_atof(gtk_entry_get_text(entry));

	while (list)
	{
		if(ft_strcmp(data->desc,"posx") == 0)
		{
			list->v0.x  += (((t_obj *)data->obj)->pos.x - oldpos.x);
			list->v1.x  += (((t_obj *)data->obj)->pos.x - oldpos.x);
			list->v2.x  += (((t_obj *)data->obj)->pos.x - oldpos.x);
		}
		else if(ft_strcmp(data->desc,"posy") == 0)
		{
			list->v0.y  += (((t_obj *)data->obj)->pos.y - oldpos.y);
			list->v1.y  += (((t_obj *)data->obj)->pos.y - oldpos.y);
			list->v2.y  += (((t_obj *)data->obj)->pos.y - oldpos.y);
		}
		else if(ft_strcmp(data->desc,"posz") == 0)
		{
			list->v0.z += (((t_obj *)data->obj)->pos.z - oldpos.z);
			list->v1.z += (((t_obj *)data->obj)->pos.z - oldpos.z);
			list->v2.z += (((t_obj *)data->obj)->pos.z - oldpos.z);
		}
		list = list->next;
	}
}

void	save_entry_transformation_object(GtkEntry *entry, t_gtkData *data)
{
	float ret;
	t_vect pos;
	

	ret = ft_atof(gtk_entry_get_text(entry));
	pos = ((t_obj *)data->obj)->pos;
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

	if (((t_obj *)data->obj)->type == MESH )
	{
		if(ft_strcmp(data->desc,"posx") == 0 || ft_strcmp(data->desc,"posy") == 0||ft_strcmp(data->desc,"posz") == 0)
		{
			save_translation_mesh_object(entry,data, pos);
		}
	}
}

void	save_entry_material_object(GtkEntry *entry, t_gtkData *data)
{
	float ret_f;
	int ret_i;
	char *ret_s;

	if(ft_strcmp(data->desc,"shiny") == 0)
	{
		ret_f = ft_atof(gtk_entry_get_text(entry));
		((t_obj *)data->obj)->mater.shiny  = ret_f;
	}
	if(ft_strcmp(data->desc,"refl") == 0)
	{
		ret_f = ft_atof(gtk_entry_get_text(entry));
		((t_obj *)data->obj)->mater.int_refl = ret_f;
	}
	if(ft_strcmp(data->desc,"trans") == 0)
	{
		ret_f = ft_atof(gtk_entry_get_text(entry));
		((t_obj *)data->obj)->mater.int_trans = ret_f;
	}
	if(ft_strcmp(data->desc,"colr") == 0)
	{
		ret_i = ft_atoi(gtk_entry_get_text(entry));
		((t_obj *)data->obj)->mater.color.r  = ret_i;
	}
	if(ft_strcmp(data->desc,"colg") == 0)
	{
		ret_i = ft_atoi(gtk_entry_get_text(entry));
		((t_obj *)data->obj)->mater.color.g  = ret_i;
	}
	if(ft_strcmp(data->desc,"colb") == 0)
	{
		ret_i = ft_atoi(gtk_entry_get_text(entry));
		((t_obj *)data->obj)->mater.color.b = ret_i;
	}
	if(ft_strcmp(data->desc,"text") == 0)
	{
		ret_s = (char *)gtk_entry_get_text(entry);
		// ((t_obj *)data->obj)->mater.text = ret_s;
	}
}

void	select_text(GtkEntry *entry, t_gtkData *data){
	GtkWidget *dialog;
	(void)entry;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	gint res;

	dialog = gtk_file_chooser_dialog_new ("Open File",GTK_WINDOW(g_env.win),action,"_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT,NULL);

	res = gtk_dialog_run (GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
	    char *filename;
	    GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
	    filename = gtk_file_chooser_get_filename (chooser);
	    //free(((t_obj *)data->obj)->mater.tex->text);
	    //free(((t_obj *)data->obj)->mater.tex);
	    ((t_obj *)data->obj)->mater.tex = load_texture(filename);
	    g_free (filename);
	}
	launch_preview();
	gtk_widget_destroy (dialog);
}

void	save_entry_material_light(GtkEntry *entry, t_gtkData *data)
{
	float ret_f;
	int ret_i;

	if(ft_strcmp(data->desc,"intens") == 0)
	{
		ret_f = ft_atof(gtk_entry_get_text(entry));
		((t_light *)data->obj)->intensity  = ret_f;
	}
	if(ft_strcmp(data->desc,"blur") == 0)
	{
		ret_i = ft_atoi(gtk_entry_get_text(entry));
		((t_light *)data->obj)->blur = ret_f;
	}
	if(ft_strcmp(data->desc,"colr") == 0)
	{
		ret_i = ft_atoi(gtk_entry_get_text(entry));
		((t_light *)data->obj)->color.r  = ret_i;
	}
	if(ft_strcmp(data->desc,"colg") == 0)
	{
		ret_i = ft_atoi(gtk_entry_get_text(entry));
		((t_light *)data->obj)->color.g  = ret_i;
	}
	if(ft_strcmp(data->desc,"colb") == 0)
	{
		ret_i = ft_atoi(gtk_entry_get_text(entry));
		((t_light *)data->obj)->color.b = ret_i;
	}
}
void	create_material_widget_object(void *object, GtkWidget *grid)
{
	GtkWidget *shiny_label;
	GtkWidget *refl_label;
	GtkWidget *trans_label;
	GtkWidget *color_label;
	GtkWidget *text_label;

	GtkWidget *shiny_entry;
	GtkWidget *refl_entry;
	GtkWidget *trans_entry;
	GtkWidget *color_r_entry;
	GtkWidget *color_g_entry;
	GtkWidget *color_b_entry;
	GtkWidget *text_entry;
	GtkWidget *btn_text;
	GtkWidget *color_button;

	GtkEntryBuffer *shiny_buffer;
	GtkEntryBuffer *refl_buffer;
	GtkEntryBuffer *trans_buffer;
	GtkEntryBuffer *color_r_buffer;
	GtkEntryBuffer *color_g_buffer;
	GtkEntryBuffer *color_b_buffer;
	GtkEntryBuffer *text_buffer;

	t_obj *current_obj;
	char *s_entry = NULL;
	t_gtkData *entry_shiny = NULL;
	t_gtkData *entry_refl = NULL;
	t_gtkData *entry_trans = NULL;
	t_gtkData *entry_col_r = NULL;
	t_gtkData *entry_col_g = NULL;
	t_gtkData *entry_col_b = NULL;
	t_gtkData *entry_text = NULL;
	t_gtkData *entry_col = NULL;
	GdkRGBA *col = malloc(sizeof(GdkRGBA));


	s_entry = malloc(sizeof(char) * 10);
	entry_shiny = malloc(sizeof(t_gtkData));
	entry_refl = malloc(sizeof(t_gtkData));
	entry_trans = malloc(sizeof(t_gtkData));
	entry_col_r= malloc(sizeof(t_gtkData));
	entry_col_g = malloc(sizeof(t_gtkData));
	entry_col_b = malloc(sizeof(t_gtkData));
	entry_text = malloc(sizeof(t_gtkData));
	entry_col = malloc(sizeof(t_gtkData));
	current_obj = (t_obj *)object;
	sprintf(s_entry,"%f", current_obj->mater.shiny);
	shiny_buffer = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%f", current_obj->mater.int_refl);
	refl_buffer = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%f", current_obj->mater.int_trans);
	trans_buffer = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%d", current_obj->mater.color.r);
	color_r_buffer = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%d", current_obj->mater.color.g);
	color_g_buffer = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%d", current_obj->mater.color.b);
	color_b_buffer = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	// sprintf(s_entry,"%s", current_obj->mater.text);
	text_buffer = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));

	free(s_entry);

	shiny_label = gtk_label_new("Brillance");
	refl_label = gtk_label_new("Reflection");
	trans_label = gtk_label_new("Transparence");
	color_label = gtk_label_new("Color");
	text_label = gtk_label_new("Texture");

	shiny_entry = gtk_entry_new_with_buffer(shiny_buffer);
	refl_entry = gtk_entry_new_with_buffer(refl_buffer);
	trans_entry = gtk_entry_new_with_buffer(trans_buffer);
	color_r_entry = gtk_entry_new_with_buffer(color_r_buffer);
	color_g_entry = gtk_entry_new_with_buffer(color_g_buffer);
	color_b_entry = gtk_entry_new_with_buffer(color_b_buffer);
	text_entry = gtk_entry_new_with_buffer(text_buffer);
	btn_text = gtk_button_new_with_label ("Select texture");

	col->red  = (double)current_obj->mater.color.r / 255;
	col->green  = (double)current_obj->mater.color.g / 255;
	col->blue  = (double)current_obj->mater.color.b / 255;
	col->alpha = 1;

	color_button = gtk_color_button_new_with_rgba ((const GdkRGBA *)col);
	entry_col->data = color_button;
	entry_col->desc = ft_strdup("color");
	entry_col->obj = current_obj;

	gtk_entry_set_width_chars ((GtkEntry *)shiny_entry, 6);
	gtk_entry_set_width_chars ((GtkEntry *)refl_entry, 6);
	gtk_entry_set_width_chars ((GtkEntry *)trans_entry, 6);
	gtk_entry_set_width_chars ((GtkEntry *)color_r_entry, 3);
	gtk_entry_set_width_chars ((GtkEntry *)color_g_entry, 3);
	gtk_entry_set_width_chars ((GtkEntry *)color_b_entry, 3);
	gtk_entry_set_width_chars ((GtkEntry *)text_entry, 6);
	gtk_entry_set_max_length ((GtkEntry *)shiny_entry, 6);
	gtk_entry_set_max_length ((GtkEntry *)refl_entry, 6);
	gtk_entry_set_max_length ((GtkEntry *)trans_entry, 6);
	gtk_entry_set_max_length ((GtkEntry *)color_r_entry, 3);
	gtk_entry_set_max_length ((GtkEntry *)color_g_entry, 3);
	gtk_entry_set_max_length ((GtkEntry *)color_b_entry, 3);
	gtk_entry_set_max_length ((GtkEntry *)text_entry, 6);

	gtk_grid_attach(GTK_GRID(grid), shiny_label,0,0,1,1);
	gtk_grid_attach(GTK_GRID(grid), refl_label,0,1,1,1);
	gtk_grid_attach(GTK_GRID(grid), trans_label,0,2,1,1);
	gtk_grid_attach(GTK_GRID(grid), color_label,0,3,1,1);
	gtk_grid_attach(GTK_GRID(grid), text_label,0,4,1,1);

	gtk_grid_attach(GTK_GRID(grid), shiny_entry,1,0,1,1);
	gtk_grid_attach(GTK_GRID(grid), refl_entry,1,1,1,1);
	gtk_grid_attach(GTK_GRID(grid), trans_entry,1,2,1,1);
	gtk_grid_attach(GTK_GRID(grid), color_r_entry,1,3,1,1);
	gtk_grid_attach(GTK_GRID(grid), color_g_entry,2,3,1,1);
	gtk_grid_attach(GTK_GRID(grid), color_b_entry,3,3,1,1);
	gtk_grid_attach(GTK_GRID(grid), color_button,4,3,1,1);
	gtk_grid_attach(GTK_GRID(grid), text_entry,1,4,1,1);
	gtk_grid_attach(GTK_GRID(grid), btn_text,2,4,1,1);

	entry_shiny->data = shiny_entry;
	entry_shiny->desc = ft_strdup("shiny");
	entry_shiny->obj = current_obj;

	entry_refl->data = refl_entry;
	entry_refl->desc = ft_strdup("refl");
	entry_refl->obj = current_obj;

	entry_trans->data = trans_entry;
	entry_trans->desc = ft_strdup("trans");
	entry_trans->obj = current_obj;

	entry_col_r->data = color_r_entry;
	entry_col_r->desc = ft_strdup("colr");
	entry_col_r->obj = current_obj;

	entry_col_g->data = color_g_entry;
	entry_col_g->desc = ft_strdup("colg");
	entry_col_g->obj = current_obj;

	entry_col_b->data = color_b_entry;
	entry_col_b->desc = ft_strdup("colb");
	entry_col_b->obj = current_obj;

	entry_text->data = text_entry;
	entry_text->desc = ft_strdup("text");
	entry_text->obj = current_obj;

	g_signal_connect(shiny_entry, "changed",
			G_CALLBACK(save_entry_material_object), entry_shiny);
	g_signal_connect(refl_entry, "changed",
			G_CALLBACK(save_entry_material_object), entry_refl);
	g_signal_connect(trans_entry, "changed",
			G_CALLBACK(save_entry_material_object), entry_trans);
	g_signal_connect(color_r_entry, "changed",
			G_CALLBACK(save_entry_material_object), entry_col_r);
	g_signal_connect(color_g_entry, "changed",
			G_CALLBACK(save_entry_material_object), entry_col_g);
	g_signal_connect(color_b_entry, "changed",
			G_CALLBACK(save_entry_material_object), entry_col_b);
	g_signal_connect(text_entry, "changed",
			G_CALLBACK(save_entry_material_object), entry_text);
	g_signal_connect(btn_text, "clicked",
	 		G_CALLBACK(select_text), entry_text);

	g_signal_connect(shiny_entry, "changed",
			G_CALLBACK(launch_preview), entry_shiny);
	g_signal_connect(refl_entry, "changed",
			G_CALLBACK(launch_preview), entry_refl);
	g_signal_connect(trans_entry, "changed",
			G_CALLBACK(launch_preview), entry_trans);
	g_signal_connect(color_r_entry, "changed",
			G_CALLBACK(launch_preview), entry_col_r);
	g_signal_connect(color_g_entry, "changed",
			G_CALLBACK(launch_preview), entry_col_g);
	g_signal_connect(color_b_entry, "changed",
			G_CALLBACK(launch_preview), entry_col_b);
	g_signal_connect(text_entry, "changed",
			G_CALLBACK(launch_preview), entry_text);

	g_signal_connect(color_button, "color-set",
			G_CALLBACK(save_color_material), entry_col);
	g_signal_connect(color_button, "color-set",
			G_CALLBACK(launch_preview), entry_col);
}

void	create_material_widget_light(void *object, GtkWidget *grid)
{
	GtkWidget *intensity_label;
	GtkWidget *blur_label;
	GtkWidget *color_label;

	GtkWidget *intensity_entry;
	GtkWidget *blur_entry;
	GtkWidget *color_r_entry;
	GtkWidget *color_g_entry;
	GtkWidget *color_b_entry;
	GtkWidget *color_button;

	GtkEntryBuffer *intensity_buffer;
	GtkEntryBuffer *blur_buffer;
	GtkEntryBuffer *color_r_buffer;
	GtkEntryBuffer *color_g_buffer;
	GtkEntryBuffer *color_b_buffer;

	t_light *current_obj;
	char *s_entry = NULL;
	t_gtkData *entry_intensity = NULL;
	t_gtkData *entry_blur = NULL;
	t_gtkData *entry_col_r = NULL;
	t_gtkData *entry_col_g = NULL;
	t_gtkData *entry_col_b = NULL;
	t_gtkData *entry_col = NULL;

	GdkRGBA *col = malloc(sizeof(GdkRGBA));

	s_entry = malloc(sizeof(char) * 10);
	entry_intensity = malloc(sizeof(t_gtkData));
	entry_blur = malloc(sizeof(t_gtkData));
	entry_col_r= malloc(sizeof(t_gtkData));
	entry_col_g = malloc(sizeof(t_gtkData));
	entry_col_b = malloc(sizeof(t_gtkData));
	entry_col = malloc(sizeof(t_gtkData));
	current_obj = (t_light *)object;
	sprintf(s_entry,"%f", current_obj->intensity);
	intensity_buffer = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%d", current_obj->blur);
	blur_buffer = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%d", current_obj->color.r);
	color_r_buffer = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%d", current_obj->color.g);
	color_g_buffer = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));
	sprintf(s_entry,"%d", current_obj->color.b);
	color_b_buffer = gtk_entry_buffer_new(s_entry,ft_strlen(s_entry));

	free(s_entry);

	intensity_label = gtk_label_new("Intensite");
	blur_label = gtk_label_new("Blur");
	color_label = gtk_label_new("Color");

	intensity_entry = gtk_entry_new_with_buffer(intensity_buffer);
	blur_entry = gtk_entry_new_with_buffer(blur_buffer);
	color_r_entry = gtk_entry_new_with_buffer(color_r_buffer);
	color_g_entry = gtk_entry_new_with_buffer(color_g_buffer);
	color_b_entry = gtk_entry_new_with_buffer(color_b_buffer);

	col->red  = (double)current_obj->color.r / 255;
	col->green  = (double)current_obj->color.g / 255;
	col->blue  = (double)current_obj->color.b / 255;
	col->alpha = 1;

	color_button = gtk_color_button_new_with_rgba ((const GdkRGBA *)col);
	entry_col->data = color_button;
	entry_col->desc = ft_strdup("color");
	entry_col->obj = current_obj;

	gtk_entry_set_width_chars ((GtkEntry *)intensity_entry, 6);
	gtk_entry_set_width_chars ((GtkEntry *)blur_entry, 6);
	gtk_entry_set_width_chars ((GtkEntry *)color_r_entry, 3);
	gtk_entry_set_width_chars ((GtkEntry *)color_g_entry, 3);
	gtk_entry_set_width_chars ((GtkEntry *)color_b_entry, 3);
	gtk_entry_set_max_length ((GtkEntry *)intensity_entry, 6);
	gtk_entry_set_max_length ((GtkEntry *)blur_entry, 6);
	gtk_entry_set_max_length ((GtkEntry *)color_r_entry, 3);
	gtk_entry_set_max_length ((GtkEntry *)color_g_entry, 3);
	gtk_entry_set_max_length ((GtkEntry *)color_b_entry, 3);

	gtk_grid_attach(GTK_GRID(grid), intensity_label,0,0,1,1);
	gtk_grid_attach(GTK_GRID(grid), blur_label,0,1,1,1);
	gtk_grid_attach(GTK_GRID(grid), color_label,0,2,1,1);

	gtk_grid_attach(GTK_GRID(grid), intensity_entry,1,0,1,1);
	gtk_grid_attach(GTK_GRID(grid), blur_entry,1,1,1,1);
	gtk_grid_attach(GTK_GRID(grid), color_r_entry,1,2,1,1);
	gtk_grid_attach(GTK_GRID(grid), color_g_entry,2,2,1,1);
	gtk_grid_attach(GTK_GRID(grid), color_b_entry,3,2,1,1);
	gtk_grid_attach(GTK_GRID(grid), color_button,4,2,1,1);

	entry_intensity->data = intensity_entry;
	entry_intensity->desc = ft_strdup("intens");
	entry_intensity->obj = current_obj;

	entry_blur->data = blur_entry;
	entry_blur->desc = ft_strdup("blur");
	entry_blur->obj = current_obj;

	entry_col_r->data = color_r_entry;
	entry_col_r->desc = ft_strdup("colr");
	entry_col_r->obj = current_obj;

	entry_col_g->data = color_g_entry;
	entry_col_g->desc = ft_strdup("colg");
	entry_col_g->obj = current_obj;

	entry_col_b->data = color_b_entry;
	entry_col_b->desc = ft_strdup("colb");
	entry_col_b->obj = current_obj;

	g_signal_connect(intensity_entry, "changed",
			G_CALLBACK(save_entry_material_light), entry_intensity);
	g_signal_connect(blur_entry, "changed",
			G_CALLBACK(save_entry_material_light), entry_blur);
	g_signal_connect(color_r_entry, "changed",
			G_CALLBACK(save_entry_material_light), entry_col_r);
	g_signal_connect(color_g_entry, "changed",
			G_CALLBACK(save_entry_material_light), entry_col_g);
	g_signal_connect(color_b_entry, "changed",
			G_CALLBACK(save_entry_material_light), entry_col_b);

	g_signal_connect(intensity_entry, "changed",
			G_CALLBACK(launch_preview), entry_intensity);
	g_signal_connect(blur_entry, "changed",
			G_CALLBACK(launch_preview), entry_blur);
	g_signal_connect(color_r_entry, "changed",
			G_CALLBACK(launch_preview), entry_col_r);
	g_signal_connect(color_g_entry, "changed",
			G_CALLBACK(launch_preview), entry_col_g);
	g_signal_connect(color_b_entry, "changed",
			G_CALLBACK(launch_preview), entry_col_b);


	g_signal_connect(color_button, "color-set",
			G_CALLBACK(save_color_material_light), entry_col);
	g_signal_connect(color_button, "color-set",
			G_CALLBACK(launch_preview), entry_col);
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

	g_signal_connect(pos_entry[0], "changed",
			G_CALLBACK(launch_preview), entry_posx);
	g_signal_connect(pos_entry[1], "changed",
			G_CALLBACK(launch_preview), entry_posy);
	g_signal_connect(pos_entry[2], "changed",
			G_CALLBACK(launch_preview), entry_posz);
	g_signal_connect(dir_entry[0], "changed",
			G_CALLBACK(launch_preview), entry_dirx);
	g_signal_connect(dir_entry[1], "changed",
			G_CALLBACK(launch_preview), entry_diry);
	g_signal_connect(dir_entry[2], "changed",
			G_CALLBACK(launch_preview), entry_dirz);
	g_signal_connect(rayon_entry, "changed",
			G_CALLBACK(launch_preview), entry_rayon);
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

	g_signal_connect(pos_entry[0], "changed",
			G_CALLBACK(launch_preview), entry_posx);
	g_signal_connect(pos_entry[1], "changed",
			G_CALLBACK(launch_preview), entry_posy);
	g_signal_connect(pos_entry[2], "changed",
			G_CALLBACK(launch_preview), entry_posz);
	g_signal_connect(rayon_entry, "changed",
			G_CALLBACK(launch_preview), entry_rayon);
}

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
 void
  view_popup_menu_delete_row (GtkWidget *menuitem, gpointer userdata)
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

  void
  view_popup_menu (GtkWidget *treeview, GdkEventButton *event,GtkTreePath *path, gpointer userdata)
  {
    GtkWidget *menu, *menuitem;

    menu = gtk_menu_new();
    (void)userdata;
    (void)treeview;
    menuitem = gtk_menu_item_new_with_label("Delete");

    g_signal_connect(menuitem, "activate",
                     (GCallback) view_popup_menu_delete_row , path);

    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuitem);

    gtk_widget_show_all(menu);

    gtk_menu_popup_at_pointer(GTK_MENU(menu),(GdkEvent*)event);
  }


  gboolean
  view_onButtonPressed (GtkWidget *treeview, GdkEventButton *event, gpointer userdata)
  {
    GtkTreePath *path = NULL;
    GtkTreeSelection *selection;

    if (event->type == GDK_BUTTON_PRESS  &&  event->button == 3)
    {
     if (1)
     {
       selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));

       if (gtk_tree_selection_count_selected_rows(selection)  <= 1)
       {

          if (gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(treeview),
                                            (gint) event->x,
                                            (gint) event->y,
                                            &path, NULL, NULL, NULL))
          {
            gtk_tree_selection_unselect_all(selection);
            gtk_tree_selection_select_path(selection, path);
          }
       }
     }
      view_popup_menu(treeview, event,path, userdata);
      return TRUE;
    }
    return FALSE;
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
	gtk_list_store_clear (model);
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
	static int i = 0 ;

	if (i == 0)
	{
		gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view),
			GTK_TREE_VIEW_COLUMN(column));
		i++;
	}

	g_signal_connect(tree_view, "row-activated", (GCallback) select_current_obj,
			NULL);
	g_signal_connect(tree_view, "button-press-event", (GCallback) view_onButtonPressed, NULL);
}
