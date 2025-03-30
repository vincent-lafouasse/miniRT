/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_point_light_array.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 01:06:43 by poss              #+#    #+#             */
/*   Updated: 2025/03/30 01:08:04 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_POINT_LIGHT_ARRAY_H
# define T_POINT_LIGHT_ARRAY_H

# include "../t_point_light.h"
# include <stdbool.h>
# include <stddef.h>

struct	s_point_light_array
{
	size_t			cap;
	size_t			len;
	t_point_light	data[];
};
typedef struct s_point_light_array	t_point_light_array;

t_point_light_array	*point_light_array_new(size_t cap);

typedef bool						t_is_full;
t_is_full			point_light_array_push(t_point_light_array *self,
						t_point_light point_light);

void				point_light_array_destroy(t_point_light_array **self);

#endif // T_POINT_LIGHT_ARRAY_H
