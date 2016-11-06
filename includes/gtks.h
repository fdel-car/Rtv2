#ifndef GTKS_H
# define GTKS_H

typedef struct		s_gtkData
{
	GtkWidget		*data;
	void			*obj;
	char 			*desc;
}					t_gtkData;

void create_list_of_objects();
void select_current_obj(GtkTreeView *GtkTreeView, GtkTreePath *path);

#endif