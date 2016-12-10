/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhuver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 12:43:28 by bhuver            #+#    #+#             */
/*   Updated: 2016/12/10 18:38:38 by bhuver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static float		perlin_noise(t_noise n, float x, float y)
{
	n.tempx = x - n.x0;
	n.tempy = y - n.y0;
	n.s = n.gradtab[n.gr0][0] * n.tempx + n.gradtab[n.gr0][1] * n.tempy;
	n.tempx = x - (n.x0 + 1);
	n.tempy = y - n.y0;
	n.t = n.gradtab[n.gr1][0] * n.tempx + n.gradtab[n.gr1][1] * n.tempy;
	n.tempx = x - n.x0;
	n.tempy = y - (n.y0 + 1);
	n.u = n.gradtab[n.gr2][0] * n.tempx + n.gradtab[n.gr2][1] * n.tempy;
	n.tempx = x - (n.x0 + 1);
	n.tempy = y - (n.y0 + 1);
	n.v = n.gradtab[n.gr3][0] * n.tempx + n.gradtab[n.gr3][1] * n.tempy;
	n.tmp = x - n.x0;
	n.cx = 3 * n.tmp * n.tmp - 2 * n.tmp * n.tmp * n.tmp;
	n.li1 = n.s + n.cx * (n.t - n.s);
	n.li2 = n.u + n.cx * (n.v - n.u);
	n.tmp = y - n.y0;
	n.cy = 3 * n.tmp * n.tmp - 2 * n.tmp * n.tmp * n.tmp;
	return (n.li1 + n.cy * (n.li2 - n.li1));
}

void				get_permtab(t_noise *n)
{
	static int perm[] = { 151, 160, 137, 91, 90, 15, 131, 13, 201, 95,
	96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21,
	10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219,
	203, 117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125,
	136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166, 77, 146,
	158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55,
	46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209,
	76, 132, 187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86,
	164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202,
	38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182,
	189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221,
	153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113,
	224, 232, 178, 185, 112, 104, 218, 246, 97, 228, 251, 34, 242, 193, 238,
	210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239, 107, 49,
	192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45,
	127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141,
	128, 195, 78, 66, 215, 61, 156, 180 };

	n->gr0 = perm[n->ii + perm[n->jj]] % 8;
	n->gr1 = perm[n->ii + 1 + perm[n->jj]] % 8;
	n->gr2 = perm[n->ii + perm[n->jj + 1]] % 8;
	n->gr3 = perm[n->ii + 1 + perm[n->jj + 1]] % 8;
}

static float		init_vars(t_noise n, float x, float y, float reso)
{
	x /= reso;
	y /= reso;
	n.x0 = (int)x;
	n.y0 = (int)y;
	n.ii = n.x0 & 255;
	n.jj = n.y0 & 255;
	get_permtab(&n);
	return (perlin_noise(n, x, y) * 0.5 * 255);
}

static void			init_gradient_tab(t_noise *n)
{
	n->unit = 1.0 - sqrt(2);
	n->gradtab[0][0] = n->unit;
	n->gradtab[0][1] = n->unit;
	n->gradtab[1][0] = -n->unit;
	n->gradtab[1][1] = n->unit;
	n->gradtab[2][0] = n->unit;
	n->gradtab[2][1] = -n->unit;
	n->gradtab[3][0] = -n->unit;
	n->gradtab[3][1] = -n->unit;
	n->gradtab[4][0] = 1;
	n->gradtab[4][1] = 0;
	n->gradtab[5][0] = -1;
	n->gradtab[5][1] = 0;
	n->gradtab[6][0] = 0;
	n->gradtab[6][1] = 1;
	n->gradtab[7][0] = 0;
	n->gradtab[7][1] = -1;
}

void				generate_perlin_tex(t_text *tex, float index)
{
	float		x;
	float		y;
	float		value;
	t_noise		n;
	int			ref;

	ref = 0;
	y = 0;
	init_gradient_tab(&n);
	while (y < tex->tex_h)
	{
		x = 0;
		while (x < tex->tex_w)
		{
			value = init_vars(n, x, y, index);
			tex->text[ref++] = value;
			tex->text[ref++] = value;
			tex->text[ref++] = value;
			x++;
		}
		y++;
	}
}
