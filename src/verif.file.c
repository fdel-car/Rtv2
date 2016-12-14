/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 17:28:56 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/14 13:24:56 by bhuver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		verif_elem(char **t)
{
	int i;
	int	se;

	i = 1;
	if (!t[i] || !ft_sii(t[i], "{"))
		return (0);
	if ((se = count_esize(&(t[i]))) <= 0)
		return (0);
	while (t[++i] && --se > 1)
		;
	if (!t[i] || !ft_sii(t[i], "}"))
		return (0);
	return (1);
}

int		verif_gelem(char **t)
{
	int i;
	int tab[3];

	i = 1;
	if (!t[i] || !ft_sii(t[i], "{") || (tab[0] = count_esize(&(t[i]))) <= 0)
		return (0);
	while (t[++i] && --tab[0] > 1)
	{
		tab[1] = i;
		while (is_blank(t[tab[1]]))
			tab[1]++;
		tab[1] = tab[1] - i;
		i += tab[1];
		tab[0] -= tab[1];
		if (!verif_elem(&(t[i])))
			return (0);
		++i;
		tab[0]--;
		tab[2] = count_esize(&(t[i])) - 1;
		i += tab[2];
		tab[0] -= tab[2];
	}
	if (!t[i] || !ft_sii(t[i], "}"))
		return (0);
	return (1);
}

int		verif_scene(char **t)
{
	int	i;
	int	se;
	int	r;

	i = 1;
	r = 1;
	if (!t[i] || !ft_sii(t[i], "{"))
		return (0);
	if ((se = count_esize(&(t[i]))) <= 0)
		return (0);
	while (t[++i] && --se > 1)
	{
		if (is_sim(t[i], "camera"))
			r = !verif_elem(&(t[i])) ? 0 : r;
		if (is_sim(t[i], "objects"))
			r = !verif_gelem(&(t[i])) ? 0 : r;
		if (is_sim(t[i], "lights"))
			r = !verif_gelem(&(t[i])) ? 0 : r;
	}
	return (r);
}

int		verif_file(char **t)
{
	int	n;
	int	r;

	n = -1;
	r = 0;
	while (t[++n])
		if (is_sim(t[n], "scene"))
			r = verif_scene(&(t[n]));
	return (r);
}
