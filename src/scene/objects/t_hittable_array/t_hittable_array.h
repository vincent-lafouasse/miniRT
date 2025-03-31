/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_hittable_array.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 19:03:51 by poss              #+#    #+#             */
/*   Updated: 2025/03/31 19:04:22 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_HITTABLE_ARRAY_H
# define T_HITTABLE_ARRAY_H

# include "../t_hittable.h"
# include "math/t_interval/t_interval.h"
# include <stdbool.h>
# include <stddef.h>

struct	s_hittable_array
{
	size_t		cap;
	size_t		len;
	t_hittable	data[];
};
typedef struct s_hittable_array	t_hittable_array;

t_hittable_array	*hittable_array_new(size_t cap);

typedef bool					t_is_full;
t_is_full			hittable_array_push(t_hittable_array *self,
						t_hittable hittable);

bool				hittable_array_hit(const t_hittable_array *self,
						t_interval range, t_ray ray,
						t_hit_record *rec_out);

void				hittable_array_destroy(t_hittable_array **self);

#endif // T_HITTABLE_ARRAY_H
