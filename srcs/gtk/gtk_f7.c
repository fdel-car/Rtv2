/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_f7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 19:38:37 by fdel-car          #+#    #+#             */
/*   Updated: 2019/09/02 15:16:35 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void delete_objects1(t_obj *list_obj, t_obj *current_obj)
{
	if (list_obj == current_obj)
	{
		g_env.scene.obj = list_obj->next;
		free(current_obj->name);
		free(current_obj);
	}
	else
	{
		while (list_obj)
		{
			if (list_obj->next == current_obj)
			{
				list_obj->next = current_obj->next;
				free(current_obj->name);
				free(current_obj);
			}
			list_obj = list_obj->next;
		}
	}
}

void delete_objects2(t_light *current_light, t_light *list_lgt)
{
	if (list_lgt == current_light)
	{
		g_env.scene.lgt = list_lgt->next;
		free(current_light->name);
		free(current_light);
	}
	else
	{
		while (list_lgt)
		{
			if (list_lgt->next == current_light)
			{
				list_lgt->next = current_light->next;
				free(current_light->name);
				free(current_light);
			}
			list_lgt = list_lgt->next;
		}
	}
}

void delete_objects(void *obj, unsigned int n)
{
	t_obj *list_obj;
	t_obj *current_obj;
	t_light *current_light;
	t_light *list_lgt;

	list_obj = g_env.scene.obj;
	list_lgt = g_env.scene.lgt;
	if (n == 1)
	{
		current_obj = (t_obj *)obj;
		delete_objects1(list_obj, current_obj);
	}
	else if (n == 2)
	{
		current_light = (t_light *)obj;
		delete_objects2(current_light, list_lgt);
	}
}

void *find_objects(char *name, unsigned int *n)
{
	t_light *light;
	t_obj *obj;

	light = g_env.scene.lgt;
	obj = g_env.scene.obj;
	while (obj)
	{
		if (strcmp(obj->name, name) == 0)
			{
				*n = 1;
				return (obj);
			}
		obj = obj->next;
	}
	while (light)
	{
		if (strcmp(light->name, name) == 0)
			{
				*n = 2;
				return (light);
			}
		light = light->next;
	}
	return (NULL);
}
