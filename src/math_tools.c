/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 13:55:38 by fdel-car          #+#    #+#             */
/*   Updated: 2016/11/16 05:20:30 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	quadratic_root(float a, float b, float c, float *roots)
{
	float	delta;
	float	solut;

	delta = SQ(b) - 4.0 * a * c;
	roots[0] = -1;
	roots[1] = -1;
	if (delta >= 0.0)
	{
		delta = sqrt(delta);
		roots[0] = (-b + delta) / (2.0 * a);
		roots[1] = (-b - delta) / (2.0 * a);
		solut = roots[0];
		roots[0] = roots[0] < roots[1] ? roots[0] : roots[1];
		roots[1] = solut < roots[1] ? roots[1] : solut;
		solut = roots[0] > EPSILON ? roots[0] : roots[1];
		if (solut > EPSILON)
			return (solut);
	}
	return (-1);
}

// float	*cubic_root(float a, float b, float c, float d)

// float	quartic_root(float a, float b, float c, float d, float e)
