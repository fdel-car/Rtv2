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
# define WIDTH 1920
# define HEIGHT 1080
# define SQ(x) ((x) * (x))

#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <math.h>
#include "libft.h"

typedef struct	s_gtk
{
	GdkPixbuf		*pix;
	GtkAdjustment	*red_adjust;
	GtkAdjustment	*green_adjust;
	GtkAdjustment	*blue_adjust;
	GtkWidget		*win;
	GtkWidget		*img;
	GtkWidget		*box;
	GtkWidget		*box_red;
	GtkWidget		*box_green;
	GtkWidget		*box_blue;
	GtkWidget		*list;
	GtkWidget		*red_scale;
	GtkWidget		*green_scale;
	GtkWidget		*blue_scale;
	GtkWidget		*button;
	GMainLoop		*loop;
	guchar			*pixels;
	guchar			red;
	guchar			green;
	guchar			blue;
	int				rowstride;
	unsigned int	pos;
}					t_gtk;

t_gtk *gtk;

#endif
