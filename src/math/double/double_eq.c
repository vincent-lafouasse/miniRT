/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_eq.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 00:22:51 by poss              #+#    #+#             */
/*   Updated: 2025/03/30 00:22:52 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "double.h"
#include <math.h>

bool	double_eq(double a, double b)
{
	double	epsilon;
	double	abs_th;
	double	diff;
	double	norm;

	epsilon = 32 * DOUBLE_EPSILON;
	abs_th = DOUBLE_MIN;
	if (a == b)
		return (true);
	diff = fabs(a - b);
	norm = fmin((fabs(a) + fabs(b)), INFINITY);
	return (diff < fmax(abs_th, epsilon * norm));
}
