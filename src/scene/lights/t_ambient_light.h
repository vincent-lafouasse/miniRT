/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ambient_light.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 01:08:46 by poss              #+#    #+#             */
/*   Updated: 2025/03/30 01:11:41 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_AMBIENT_LIGHT_H
# define T_AMBIENT_LIGHT_H

# include "error/t_error.h"
# include "math/t_rgb/t_rgb.h"

struct	s_ambient_light
{
	double	intensity;
	t_rgb	color;
};
typedef struct s_ambient_light	t_ambient_light;

t_error	ambient_light(double intensity, t_rgb color,
			t_ambient_light *out);

#endif // T_AMBIENT_LIGHT_H
