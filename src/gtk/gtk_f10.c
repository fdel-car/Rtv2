#include "rt.h"

void	save_entry_material_object(GtkEntry *entry, t_gtkdata *data)
{
	float ret_f;
	int ret_i;
	char *ret_s;
	t_obj *list;
	short type;

	type = ((t_obj *)data->obj)->type;
	list = ((t_obj *)data->obj)->lst;
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
	if (type == MESH)
	{
		while (list)
		{
			if(ft_strcmp(data->desc,"shiny") == 0)
			{
				list->mater.shiny = ((t_obj *)data->obj)->mater.shiny;
			}
			if(ft_strcmp(data->desc,"refl") == 0)
			{
				list->mater.int_refl = ((t_obj *)data->obj)->mater.int_refl;
			}
			if(ft_strcmp(data->desc,"trans") == 0)
			{
				list->mater.int_trans = ((t_obj *)data->obj)->mater.int_trans;
			}
			if(ft_strcmp(data->desc,"colr") == 0)
			{
				list->mater.color.r = ((t_obj *)data->obj)->mater.color.r;
			}
			if(ft_strcmp(data->desc,"colg") == 0)
			{
				list->mater.color.g = ((t_obj *)data->obj)->mater.color.g;
			}
			if(ft_strcmp(data->desc,"colb") == 0)
			{
				list->mater.color.b = ((t_obj *)data->obj)->mater.color.b;
			}
			list = list->next;
		}
	}
}
