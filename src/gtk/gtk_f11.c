#include "rt.h"

void	select_text(GtkEntry *entry, t_gtkdata *data)
{
	GtkWidget				*dialog;
	GtkFileChooserAction	action;
	gint					res;
	char					*filename;
	GtkFileChooser			*chooser;

	(void)entry;
	filename = 0;
	chooser = 0;
	action = GTK_FILE_CHOOSER_ACTION_OPEN;
	dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(g_env.win),
	action, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		chooser = GTK_FILE_CHOOSER(dialog);
		filename = gtk_file_chooser_get_filename(chooser);
		//appeler le free_mater si besoin slo
		//free(((t_obj *)data->obj)->mater.tex->text);
		//free(((t_obj *)data->obj)->mater.tex);
		((t_obj *)data->obj)->mater.tex = load_texture(filename);
		g_free(filename);
	}
	launch_preview();
	gtk_widget_destroy (dialog);
}

void	save_entry_material_light2(GtkEntry *entry, t_gtkdata *data,
float *ret_f, int *ret_i)
{
	if (ft_strcmp(data->desc,"blur") == 0)
	{
		*ret_i = ft_atoi(gtk_entry_get_text(entry));
		((t_light *)data->obj)->blur = *ret_f;
	}
	if (ft_strcmp(data->desc,"colr") == 0)
	{
		*ret_i = ft_atoi(gtk_entry_get_text(entry));
		((t_light *)data->obj)->color.r = *ret_i;
	}
}

void	save_entry_material_light(GtkEntry *entry, t_gtkdata *data)
{
	float	ret_f;
	int		ret_i;

	if (ft_strcmp(data->desc,"intens") == 0)
	{
		ret_f = ft_atof(gtk_entry_get_text(entry));
		((t_light *)data->obj)->intensity = ret_f;
	}
	save_entry_material_light2(entry, data, &ret_f, &ret_i);
	if (ft_strcmp(data->desc,"colg") == 0)
	{
		ret_i = ft_atoi(gtk_entry_get_text(entry));
		((t_light *)data->obj)->color.g = ret_i;
	}
	if (ft_strcmp(data->desc,"colb") == 0)
	{
		ret_i = ft_atoi(gtk_entry_get_text(entry));
		((t_light *)data->obj)->color.b = ret_i;
	}
}
