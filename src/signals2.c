/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 20:16:57 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/13 20:17:24 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	update_iter_refl(void)
{
	g_env.scene.iter_refl =
	gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(g_env.spin_refl));
}

void	aa_check(void)
{
	if (g_env.scene.anti_alia >= 16)
	{
		g_env.scene.anti_alia = 16;
		gtk_combo_box_set_active(GTK_COMBO_BOX(g_env.aa_choice), 4);
	}
	else if (g_env.scene.anti_alia >= 8 && g_env.scene.anti_alia < 16)
	{
		g_env.scene.anti_alia = 8;
		gtk_combo_box_set_active(GTK_COMBO_BOX(g_env.aa_choice), 3);
	}
	else if (g_env.scene.anti_alia >= 4 && g_env.scene.anti_alia < 8)
	{
		g_env.scene.anti_alia = 4;
		gtk_combo_box_set_active(GTK_COMBO_BOX(g_env.aa_choice), 2);
	}
	else if (g_env.scene.anti_alia >= 2 && g_env.scene.anti_alia < 4)
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
