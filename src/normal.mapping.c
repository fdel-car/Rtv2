#include "rt.h"

t_vect	bump_normal(t_color	p)
{
	t_vect	r;
	// float	n;


	r.x = (float)p.r / 255;
	r.y = (float)p.g / 255;
	r.z = (float)p.b / 255;
	r = vec_sub(vec_mult(r, 2.0), vec_new(1, 1, 1));
	// r = vec_mult(r, 0.5);
	// printf("%d %d %d\t%f %f %f\n", p.r, p.g, p.b, r.x, r.y, r.z);
	// n = p.r > 128 ? 1.0 : -1.0;
	// if (p.r > 128.0)
	// 	r.x = n * (255.0 - (float)p.r) / 255.0;
	// else
	// 	r.x = n * (128.0 - (float)p.r) / 255.0;
	// n = p.r > 128 ? 1.0 : -1.0;
	// if (p.g > 128.0)
	// 	r.y = (255.0 - (float)p.g) / 255.0;
	// else
	// 	r.y = (128.0 - (float)p.g) / 255.0;
	// if (p.b > 128.0)
	// 	r.z = (255.0 - (float)p.b) / 255.0;
	return (r);
}
