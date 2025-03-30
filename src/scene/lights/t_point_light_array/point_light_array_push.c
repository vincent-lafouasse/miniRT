/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_light_array_push.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 01:06:18 by poss              #+#    #+#             */
/*   Updated: 2025/03/30 01:06:19 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_point_light_array.h"

t_is_full	point_light_array_push(t_point_light_array *self,
		const t_point_light point_light)
{
	if (self->cap == self->len)
		return (true);
	self->data[self->len++] = point_light;
	return (false);
}
