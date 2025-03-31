/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable_array_push.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 19:03:49 by poss              #+#    #+#             */
/*   Updated: 2025/03/31 19:03:50 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hittable_array.h"

t_is_full	hittable_array_push(t_hittable_array *self,
		const t_hittable hittable)
{
	if (self->cap == self->len)
		return (true);
	self->data[self->len++] = hittable;
	return (false);
}
