/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 17:45:27 by fdel-car          #+#    #+#             */
/*   Updated: 2016/10/24 17:46:44 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	load_camera(char **t)
{
	int	n;

	n = -1;
	while (t[++n] && !ft_sii(t[n], "}"))
	{
		if (ft_sii(t[n], "pos:"))
			g_env.scene.cam.pos = read_vec(get_after(t[n], "pos:"));
		if (ft_sii(t[n], "dir:"))
			g_env.scene.cam.dir = vec_norm(read_vec(get_after(t[n], "dir:")));
	}
}

void	parse_scene(char **t)
{
	int	n;

	n = -1;
	while (t[++n])
	{
		if (ft_sii(t[n], "global_illumination:"))
			g_env.scene.gl_illum = ft_atoi(get_after(t[n],
			"global_illumination:"));
		if (ft_sii(t[n], "anti_aliasing:"))
			g_env.scene.anti_alia = ft_atoi(get_after(t[n],
			"anti_aliasing:"));
		if (ft_sii(t[n], "iter_reflection:"))
			g_env.scene.iter_refl = ft_atoi(get_after(t[n],
			"iter_reflection:"));
		if (ft_sii(t[n], "camera") && t[n + 2])
			load_camera(&(t[n + 2]));
		if (ft_sii(t[n], "lights") && t[n + 2])
			load_elems(&(t[n + 2]), 'l');
		if (ft_sii(t[n], "objects") && t[n + 2])
			load_elems(&(t[n + 2]), 'o');
	}
	g_env.scene.anti_alia = log(g_env.scene.anti_alia) / log(2);
	g_env.scene.anti_alia = g_env.scene.anti_alia >= 32 ?
	32 : g_env.scene.anti_alia;
}

void	load_scene(char **t)
{
	int	n;

	n = -1;
	while (t[++n])
		if (ft_strcmp(t[n], "scene") && t[n + 2])
		{
			parse_scene(&(t[n + 2]));
			return ;
		}
}

char	*clean_line(char *s)
{
	int i;

	i = -1;
	while (s[++i] && (s[i] == ' ' || s[i] == '\t'))
		;
	return (&(s[i]));
}

void	load_file(char *scene_file)
{
	int		fd;
	char	*line;
	char	*file[524288];
	int		n;

	n = -1;
	if ((fd = open(scene_file, O_RDONLY)) >= 0)
	{
		while (get_next_line(fd, &line) && (++n) > -42)
			file[n] = line;
		file[n] = 0;
		load_scene(file);
		ctab_free(file);
	}
}
