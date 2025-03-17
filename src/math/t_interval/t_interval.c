/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_interval.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:11:18 by poss              #+#    #+#             */
/*   Updated: 2025/03/17 19:39:06 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_interval.h"
#include <math.h>

t_interval interval_new(double min, double max) {
    return (t_interval){.min = min, .max = max};
}

double interval_size(t_interval i) {
    return i.max - i.min;
}

bool interval_contains(t_interval i, double x) {
    return i.min <= x && x <= i.max;
}

bool interval_surrounds(t_interval i, double x) {
    return i.min < x && x < i.max;
}

t_interval interval_R_plus(void) {
    return (t_interval){.min = 0.0, .max = INFINITY};
}
