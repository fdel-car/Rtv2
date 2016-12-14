/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_f12_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <slgracie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 12:46:58 by slgracie          #+#    #+#             */
/*   Updated: 2016/12/14 13:03:40 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	create_materw_object5(t_norm *me)
{
	g_signal_connect(me->refl_entry, "changed",
			G_CALLBACK(save_entry_material_object), me->entry_refl);
	g_signal_connect(me->trans_entry, "changed",
			G_CALLBACK(save_entry_material_object), me->entry_trans);
	g_signal_connect(me->color_r_entry, "changed",
			G_CALLBACK(save_entry_material_object), me->entry_col_r);
	g_signal_connect(me->color_g_entry, "changed",
			G_CALLBACK(save_entry_material_object), me->entry_col_g);
	g_signal_connect(me->color_b_entry, "changed",
			G_CALLBACK(save_entry_material_object), me->entry_col_b);
	g_signal_connect(me->text_entry, "changed",
			G_CALLBACK(save_entry_material_object), me->entry_text);
	g_signal_connect(me->btn_text, "clicked",
			G_CALLBACK(select_text), me->entry_text);
	g_signal_connect(me->ref_spin_button, "value-changed",
			G_CALLBACK(save_indice_ref), me->entry_text);
	g_signal_connect(me->shiny_entry, "changed",
			G_CALLBACK(launch_preview), me->entry_shiny);
	g_signal_connect(me->refl_entry, "changed",
			G_CALLBACK(launch_preview), me->entry_refl);
	g_signal_connect(me->trans_entry, "changed",
			G_CALLBACK(launch_preview), me->entry_trans);
	g_signal_connect(me->color_r_entry, "changed",
			G_CALLBACK(launch_preview), me->entry_col_r);
}

void	create_materw_object6(t_norm *me)
{
	g_signal_connect(me->color_g_entry, "changed",
			G_CALLBACK(launch_preview), me->entry_col_g);
	g_signal_connect(me->color_b_entry, "changed",
			G_CALLBACK(launch_preview), me->entry_col_b);
	g_signal_connect(me->text_entry, "changed",
			G_CALLBACK(launch_preview), me->entry_text);
	g_signal_connect(me->color_button, "color-set",
			G_CALLBACK(save_color_material), me->entry_col);
	g_signal_connect(me->color_button, "color-set",
			G_CALLBACK(launch_preview), me->entry_col);
}
