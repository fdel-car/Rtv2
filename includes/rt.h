/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 18:45:50 by fdel-car          #+#    #+#             */
/*   Updated: 2016/11/21 18:40:26 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# define WIDTH 1280
# define HEIGHT 720
# define WIDTH_PREVIEW 192
# define HEIGHT_PREVIEW 108
# define SQ(x) ((x) * (x))
# define CB(x) ((x) * (x) * (x))
# define QC(x) ((x) * (x) * (x) * (x))
# define NUM_THREAD 8

# include <stdlib.h>
# include <gtk/gtk.h>
# include <stdlib.h>
# include <math.h>
# include "libft.h"
# include "types.h"
# include "color.h"
# include "parser.h"
# include "raytracing.h"
# include "gtks.h"

#endif
