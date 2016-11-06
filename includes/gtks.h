/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtks.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 19:50:46 by fdel-car          #+#    #+#             */
/*   Updated: 2016/11/06 19:50:47 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GTKS_H
# define GTKS_H

typedef struct		s_gtkData
{
	GtkWidget		*data;
	void			*obj;
	char 			*desc;
}					t_gtkData;

void				create_list_of_objects();
void				select_current_obj(GtkTreeView *GtkTreeView,
					GtkTreePath *path);

#endif
