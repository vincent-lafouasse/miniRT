/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_interval.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:11:20 by poss              #+#    #+#             */
/*   Updated: 2025/03/30 00:24:11 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_INTERVAL_H
# define T_INTERVAL_H

# include <math.h>
# include <stdbool.h>

struct	s_interval
{
	double	min;
	double	max;
};
typedef struct s_interval	t_interval;

t_interval	interval_new(double min, double max);
double		interval_size(t_interval i);
bool		interval_contains(t_interval i, double x);
bool		interval_surrounds(t_interval i, double x);
t_interval	interval_R_plus(void);

#endif // T_INTERVAL_H
