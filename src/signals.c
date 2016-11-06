/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 19:02:37 by fdel-car          #+#    #+#             */
/*   Updated: 2016/11/05 19:02:39 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	aa_check()
{
	if (g_env.scene.anti_alia > 16)
	{
		g_env.scene.anti_alia = 16;
		gtk_combo_box_set_active(GTK_COMBO_BOX(g_env.aa_choice), 4);
	}
	else if (g_env.scene.anti_alia > 8 && g_env.scene.anti_alia < 16)
	{
		g_env.scene.anti_alia = 8;
		gtk_combo_box_set_active(GTK_COMBO_BOX(g_env.aa_choice), 3);
	}
	else if (g_env.scene.anti_alia > 4 && g_env.scene.anti_alia < 8)
	{
		g_env.scene.anti_alia = 4;
		gtk_combo_box_set_active(GTK_COMBO_BOX(g_env.aa_choice), 2);
	}
	else if (g_env.scene.anti_alia > 2 && g_env.scene.anti_alia < 4)
	{
		g_env.scene.anti_alia = 2;
		gtk_combo_box_set_active(GTK_COMBO_BOX(g_env.aa_choice), 1);
	}
	else if (g_env.scene.anti_alia < 2)
	{
		g_env.scene.anti_alia = 0;
		gtk_combo_box_set_active(GTK_COMBO_BOX(g_env.aa_choice), 0);
	}
}

void	switch_anti_aliasing(void)
{
	char	*s;
	int		aa;

	s = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(g_env.aa_choice));
	aa = ft_atoi(s);
	g_env.scene.anti_alia = aa;
	free(s);
}
