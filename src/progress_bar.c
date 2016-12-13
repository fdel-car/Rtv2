/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress_bar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 17:03:31 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/13 20:36:54 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		loop_intersect(t_data *ray, gboolean sh, t_obj *obj)
{
	t_obj	*lst;
	float	tmp;

	lst = NULL;
	while (obj)
	{
		if (obj->type != MESH)
		{
			if (obj->type != NONE && (sh != TRUE || obj->type != SKYBOX))
				tmp = (*obj->func)(obj, *ray);
		}
		else
		{
			lst = (lst) ? lst->next : obj->lst;
			if (lst)
				tmp = (*lst->func)(lst, *ray);
		}
		if ((tmp < ray->solut || ray->solut == -1) && tmp != -1)
		{
			ray->obj_hit = lst ? lst : obj;
			ray->solut = tmp;
		}
		if (!lst)
			obj = obj->next;
	}
}

t_data		oculus_view(t_data ray)
{
	ray.solut = intersect_sphere(g_env.scene.obj, ray);
	if (ray.solut != -1)
		ray.obj_hit = g_env.scene.obj;
	return (ray);
}

void		print_loading(void)
{
	ft_putstr(ANSI_COLOR_GREEN);
	ft_putstr("##########################################\n");
	ft_putstr(ANSI_COLOR_RESET);
}

void		display_progress_bar(void)
{
	unsigned int	i;

	if (g_env.progress_bar != 1)
		return ;
	if ((g_env.pixels_progress * 100) / g_env.total != g_env.progress)
	{
		g_env.progress = (g_env.pixels_progress * 100) / g_env.total;
		{
			if (g_env.progress % 5 == 0)
			{
				i = -1;
				system("clear");
				print_loading();
				ft_printf(ANSI_COLOR_GREEN"#"ANSI_COLOR_RESET);
				while (++i <= g_env.progress / 5)
					ft_printf(ANSI_COLOR_BLUE"--"ANSI_COLOR_RESET);
				ft_printf(ANSI_COLOR_GREEN"#\n"ANSI_COLOR_RESET);
				print_loading();
			}
		}
	}
	g_env.pixels_progress++;
}
