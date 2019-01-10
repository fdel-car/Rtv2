/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhuver <bhuver@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 13:32:20 by bhuver            #+#    #+#             */
/*   Updated: 2016/12/14 15:54:14 by bhuver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		free_exit(void)
{
	free_objects(TRUE);
	free_lights();
	gtk_main_quit();
}

void		init_tex(t_text *tex)
{
	tex->tex_w = tex->size[0];
	tex->tex_h = tex->size[1];
	tex->tsize = -1;
}
