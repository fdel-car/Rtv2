/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 18:45:50 by fdel-car          #+#    #+#             */
/*   Updated: 2018/09/19 16:08:55 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# define WIDTH g_env.width
# define HEIGHT 720
# define WIDTH_PREVIEW 192
# define HEIGHT_PREVIEW 108
# define SQ(x) ((x) * (x))
# define CB(x) ((x) * (x) * (x))
# define QC(x) ((x) * (x) * (x) * (x))
# define NUM_THREAD 8

# include <gtk/gtk.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "libft.h"
# include "types.h"
# include "color.h"
# include "parser.h"
# include "raytracing.h"
# include "gtks.h"

#endif
