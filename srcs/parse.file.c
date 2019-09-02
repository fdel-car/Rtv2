/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 17:45:27 by fdel-car          #+#    #+#             */
/*   Updated: 2019/09/02 16:28:28 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void load_camera(char **t)
{
	int n;

	n = -1;
	while (t[++n] && !ft_sii(t[n], "}"))
	{
		if (ft_sii(t[n], "pos:"))
			g_env.scene.cam.pos = read_vec(get_after(t[n], "pos:"), ';');
		if (ft_sii(t[n], "pos2:"))
			g_env.scene.cam.pos2 = read_vec(get_after(t[n], "pos2:"), ';');
		if (ft_sii(t[n], "pos3:"))
			g_env.scene.cam.pos3 = read_vec(get_after(t[n], "pos3:"), ';');
		if (ft_sii(t[n], "look:"))
			g_env.scene.cam.look_at = read_vec(get_after(t[n], "look:"), ';');
	}
	g_env.scene.cam.dir = vec_norm(vec_sub(g_env.scene.cam.look_at,
										   g_env.scene.cam.pos));
	g_env.scene.cam.dist = dist_p(g_env.scene.cam.pos,
								  g_env.scene.cam.look_at);
}

void parse_scene(char **t)
{
	int n;
	int se;

	se = count_esize(t);
	n = -1;
	while (t[++n] && --se > 1)
	{
		if (ft_sii(t[n], "ambiant_lighting:"))
			g_env.scene.ambiant = atof(get_after(t[n], "ambiant_lighting:"));
		if (ft_sii(t[n], "soft_shadow:"))
			g_env.scene.soft_shadow = atoi(get_after(t[n], "soft_shadow:"));
		if (ft_sii(t[n], "anti_aliasing:"))
			g_env.scene.anti_alia = atoi(get_after(t[n], "anti_aliasing:"));
		if (ft_sii(t[n], "iter_reflection:"))
			g_env.scene.iter_refl = atoi(get_after(t[n],
												   "iter_reflection:"));
		if (ft_sii(t[n], "iter_trans:"))
			g_env.scene.iter_trans = atoi(get_after(t[n], "iter_trans:"));
		if (ft_sii(t[n], "camera") && t[n + 2])
			load_camera(&(t[n + 2]));
		if (ft_sii(t[n], "lights") && t[n + 2])
			load_elems(&(t[n + 1]), 'l');
		if (ft_sii(t[n], "objects") && t[n + 2])
			load_elems(&(t[n + 1]), 'o');
	}
}

void load_scene(char **t)
{
	int n;

	n = -1;
	while (t[++n])
		if (strcmp(t[n], "scene") && t[n + 2])
		{
			parse_scene(&(t[n]));
			return;
		}
}

char *clean_line(char *s)
{
	int i;

	i = -1;
	while (s[++i] && (s[i] == ' ' || s[i] == '\t'))
		;
	return (&(s[i]));
}

void load_file(char *scene_file)
{
	int fd;
	char *line;
	char *file[524288];
	int n;

	n = -1;
	if (strcmp(".scn", scene_file + strlen(scene_file) - 4) == 0 &&
		(fd = open(scene_file, O_RDONLY)) >= 0)
	{
		while (get_next_line(fd, &line) && (++n) > -42)
		{
			file[n] = line;
		}
		file[n + 1] = 0;
		if (verif_file(file))
			load_scene(file);
		else
			printf("WRONG FORMAT FOR CONFIG FILE!\n");
		ctab_free(file);
		close(fd);
	}
}
