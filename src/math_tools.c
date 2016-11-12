/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 13:55:38 by fdel-car          #+#    #+#             */
/*   Updated: 2016/11/10 13:55:39 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	quadratic_root(float a, float b, float c)
{
	float	delta;
	float	t1;
	float	t2;
	float	solut;

	delta = SQ(b) - 4.0 * a * c;
	if (delta >= 0.0)
	{
		delta = sqrt(delta);
		t1 = (-b + delta) / (2.0 * a);
		t2 = (-b - delta) / (2.0 * a);
		solut = t1 < t2 && t1 > EPSILON ? t1 : t2;
		if (solut > EPSILON)
			return (solut);
	}
	return (-1);
}

// float	*cubic_root(float a, float b, float c, float d)

// float	quartic_root(float a, float b, float c, float d, float e)
