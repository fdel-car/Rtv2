/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 14:17:30 by vde-la-s          #+#    #+#             */
/*   Updated: 2016/12/10 16:32:07 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
