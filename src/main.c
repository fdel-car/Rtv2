/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/20 14:35:40 by fdel-car          #+#    #+#             */
/*   Updated: 2016/12/13 17:47:15 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	pre_launch(void)
{
	desactivate_preview();
	if ((g_env.stereo == TRUE && g_env.stereo_red == TRUE) ||
	(g_env.oculus == TRUE && g_env.oculus_left == TRUE))
	{
		g_env.scene.cam.pos = vec_sub(g_env.scene.cam.pos,
		vec_mult(g_env.scene.cam.right, DIST_INTEROCULAR / 2));
		g_env.scene.cam.dir = vec_norm(vec_sub(g_env.scene.cam.look_at,
		g_env.scene.cam.pos));
	}
	if (g_env.oculus == TRUE)
		g_env.scene.obj->pos = vec_add(g_env.scene.cam.pos,
		vec_mult(g_env.scene.cam.dir, 2));
	g_env.pixels_progress = 0;
	g_env.progress = 0;
	g_env.scene.cam.right = cross_pr(g_env.scene.cam.up, g_env.scene.cam.dir);
	g_env.scene.cam.up = cross_pr(g_env.scene.cam.dir, g_env.scene.cam.right);
	g_env.scene.cam.up_left = vec_add(g_env.scene.cam.pos,
	vec_add(vec_mult(g_env.scene.cam.dir, g_env.scene.cam.view_d),
	vec_sub(vec_mult(g_env.scene.cam.up, (g_env.scene.cam.view_h / 2.0)),
	vec_mult(g_env.scene.cam.right, (g_env.scene.cam.view_w / 2.0)))));
	pre_compute_tri(g_env.scene.obj);
	g_env.id_thread = 0;
}

void	launch_thread(void)
{
	pre_launch();
	while (g_env.id_thread < NUM_THREAD)
	{
		pthread_create(&g_env.thread[g_env.id_thread], NULL, raytracing,
				&g_env.limits[g_env.id_thread]);
		g_env.id_thread++;
	}
	g_env.id_thread = 0;
	while (g_env.id_thread < NUM_THREAD)
	{
		pthread_join(g_env.thread[g_env.id_thread], NULL);
		g_env.id_thread++;
	}
	if (g_env.stereo == TRUE)
		stereo_func();
	else if (g_env.oculus == TRUE)
		oculus_func();
	else
		gtk_image_set_from_pixbuf(GTK_IMAGE(g_env.img), g_env.pix);
	check_filter();
}

void	init_limits(void)
{
	int iter;
	int	x_column;

	iter = 0;
	x_column = WIDTH / NUM_THREAD;
	while (iter < NUM_THREAD)
	{
		g_env.limits[iter] = x_column * iter;
		iter++;
	}
	iter = 0;
	x_column = WIDTH_PREVIEW / NUM_THREAD;
	while (iter < NUM_THREAD)
	{
		g_env.limits_prev[iter] = x_column * iter;
		iter++;
	}
}

void	init_sphere_oculus(void)
{
	t_obj *obj;

	g_env.width = 1280;
	obj = (t_obj *)malloc(sizeof(t_obj));
	obj->src = NULL;
	obj->cut = vec_new(0, 0, 0);
	obj->rayon = 0.8;
	obj->min = 0;
	obj->max = 0;
	obj->sphere_cut = 0;
	obj->lst = NULL;
	obj->name = ft_strdup("sphere_oculus");
	obj->type = OCULUS;
	obj->pos = vec_add(g_env.scene.cam.pos,
	vec_mult(g_env.scene.cam.dir, 2));
	obj->mater = init_mater();
	obj->mater.indice = 0.90;
	obj->mater.int_trans = 1;
	obj->func = &intersect_sphere;
	obj->next = g_env.scene.obj;
	g_env.scene.obj = obj;
	g_env.oculus = FALSE;
	g_env.total = WIDTH * HEIGHT;
}

int		main(int argc, char **argv)
{
	if (argc < 2 || argc > 3)
		return (-1);
	if (argc == 3)
	{
		if (ft_strcmp(argv[2], "-p") != 0)
			return (-1);
		g_env.progress_bar = 1;
		load_file(argv[1]);
	}
	else
		load_file(argv[1]);
	init_sphere_oculus();
	gtk_init(&argc, &argv);
	init_limits();
	init_view();
	init_gtk();
	aa_check();
	spin_button();
	gtk_builder_connect_signals(g_env.build, NULL);
	create_list_of_objects();
	launch_thread();
	launch_preview();
	gtk_widget_show_all(g_env.win);
	gtk_main();
	return (EXIT_SUCCESS);
}
