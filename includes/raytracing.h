/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 15:43:09 by fdel-car          #+#    #+#             */
/*   Updated: 2016/10/24 15:43:12 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACING_H
# define RAYTRACING_H

float		intersect_sphere(t_obj *obj, t_data ray);
float		intersect_plane(t_obj *obj, t_data ray);
t_vect		vec_new(float x, float y, float z);
t_vect		cross_pr(t_vect u, t_vect v);
t_vect		vec_mult(t_vect u, float value);
t_vect		vec_sub(t_vect u, t_vect v);
t_vect		vec_add(t_vect u, t_vect v);
t_vect		vec_norm(t_vect u);
t_vect		rot_x(float theta, t_vect u);
t_vect		rot_y(float theta, t_vect u);
t_vect		rot_z(float theta, t_vect u);
t_vect		rot_any(t_vect u, t_vect a, float theta);
t_vect		get_norm(t_data ray);
float		dotp_vec_norm(t_vect u, t_vect v);
float		dist_p(t_vect u, t_vect v);
void		*raytracing(void *arg);
void		put_pixel(int x, int y, t_color color);
void		init_view();

#endif
