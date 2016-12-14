/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 14:17:30 by vde-la-s          #+#    #+#             */
/*   Updated: 2016/12/14 13:32:40 by bhuver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		verif_type(t_obj *o)
{
	if (o->type == NONE)
	{
		free_objs(o);
		return (1);
	}
	return (0);
}

int		count_esize(char **t)
{
	int		i;
	int		na;

	i = 0;
	na = 0;
	if (ft_sii(t[i], "{"))
		while (t[i] && (na > 0 || !i))
		{
			ft_sii(t[i], "{") ? ++na : 0;
			ft_sii(t[i], "}") ? --na : 0;
			++i;
		}
	return (!na ? i : -42);
}

int		is_blank(char *l)
{
	int	i;

	i = -1;
	while (l && l[++i])
		if (l[i] != ' ' && l[i] != '\t')
			return (0);
	return (1);
}

int		is_sim(char *t, char *s)
{
	return (!ft_strcmp(clean_line(t), clean_line(s)) ?
	1 : 0);
}

int		start_by(char *s, char *end)
{
	int	i;

	i = -1;
	while (s[++i] && end[i])
		if (s[i] != end[i])
			return (0);
	return (1);
}
