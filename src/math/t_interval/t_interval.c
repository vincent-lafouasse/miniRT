/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_interval.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:11:18 by poss              #+#    #+#             */
/*   Updated: 2025/03/17 19:14:11 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_interval.h"

double interval_size(t_interval i) {
	return i.max - i.min;
}

bool interval_contains(t_interval i, double x) {
	return i.min <= x && x <= i.max;
}

bool interval_surrounds(t_interval i, double x) {
	return i.min < x && x < i.max;
}
