/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_interval.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:11:20 by poss              #+#    #+#             */
/*   Updated: 2025/03/17 19:12:57 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_INTERVAL_H
#define T_INTERVAL_H

#include <math.h>
#include <stdbool.h>

struct s_interval {
    double min;
    double max;
};
typedef struct s_interval t_interval;

double interval_size(t_interval);
bool interval_contains(t_interval, double);
bool interval_surrounds(t_interval, double);

static t_interval interval_new(double min, double max) {
    return (t_interval){.min = min, .max = max};
}

static t_interval empty_interval(void) {
    return (t_interval){.min = INFINITY, .max = -INFINITY};
}

static t_interval interval_R(void) {
    return (t_interval){.min = -INFINITY, .max = INFINITY};
}

static t_interval interval_R_plus(void) {
    return (t_interval){.min = 0.0, .max = INFINITY};
}

#endif  // T_INTERVAL_H
