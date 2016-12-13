/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.elems.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 17:44:04 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/13 20:30:43 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_mater	load_material(char **t)
{
	t_mater	new;
	int		n;
	int		se;
	float	tsize;

	n = 1;
	tsize = -42;
	new = init_mater();
	se = count_esize(&(t[n]));
	if (ft_sii(t[n], "{"))
		while (t[++n] && --se > 1)
			load_material2(&new, &tsize, t[n]);
	if (new.tex)
		new.tex->tsize = tsize > 0 ? tsize : -42;
	return (new);
}

void	init_obj(t_obj *obj)
{
	obj->next = NULL;
	obj->src = NULL;
	obj->cut = vec_new(0, 0, 0);
	obj->min = 0;
	obj->max = 0;
	obj->sphere_cut = 0;
	obj->lst = NULL;
	obj->mater = init_mater();
	obj->name = NULL;
}

void	load_object(char **t)
{
	t_obj	*new;
	char	*name;
	int		n;
	int		se;

	new = malloc(sizeof(t_obj));
	init_obj(new);
	name = ft_strdup(*t);
	new->name = ft_strtrim(name);
	se = count_esize(&(t[1]));
	free(name);
	if ((n = 1) && ft_sii(t[n], "{"))
		while (t[++n] && --se > 1)
		{
			load_object2(new, t[n]);
			load_object3(new, t[n]);
			if (ft_sii(t[n], "materiel"))
				new->mater = load_material(&(t[n]));
		}
	if (verif_type(new))
		return ;
	if (new->src)
		parse_obj(new);
	set_func(new);
	push_obj(new);
}

void	load_light(char **t)
{
	t_light	*new;
	char	*name;
	int		n;
	int		se;

	n = 1;
	new = malloc(sizeof(t_light));
	new->next = NULL;
	name = ft_strdup(*t);
	se = count_esize(&(t[n]));
	new->name = ft_strtrim(name);
	free(name);
	if (ft_sii(t[n], "{"))
		while (t[++n] && --se > 1)
			load_light2(new, t[n]);
	push_lgt(new);
}

void	load_elems(char **t, unsigned char type)
{
	int	n;
	int	se;
	int tmp;
	int	nb;

	n = 1;
	se = count_esize(t);
	while (t[n] && --se > 1)
	{
		nb = n;
		while (is_blank(t[nb]))
			nb++;
		nb = nb - n;
		n += nb;
		se -= nb;
		type == 'l' ?
			load_light(&(t[n])) : load_object(&(t[n]));
		++n;
		tmp = count_esize(&(t[n]));
		n += tmp;
		se -= tmp;
	}
}
