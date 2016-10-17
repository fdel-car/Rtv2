/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 18:45:50 by fdel-car          #+#    #+#             */
/*   Updated: 2016/09/05 18:49:48 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# define WIDTH 720
# define HEIGHT 480
# define SQ(x) ((x) * (x))

#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "libft.h"

typedef struct	s_gtk
{
	GtkWidget		*win;
	GdkPixbuf		*pix;
	GtkWidget		*img;
	GtkWidget		*grid;
	GtkWidget		*list;
	GMainLoop		*loop;
	guchar			*pixels;
	int				rowstride;
	unsigned int	pos;
	float			time;
}					t_gtk;

t_gtk *gtk;

#endif
