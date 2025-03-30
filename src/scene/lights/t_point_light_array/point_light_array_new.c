/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_light_array_new.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 01:06:15 by poss              #+#    #+#             */
/*   Updated: 2025/03/30 01:06:16 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./t_point_light_array.h"
#include <stdlib.h>

t_point_light_array	*point_light_array_new(size_t cap)
{
	t_point_light_array	*alloc;

	alloc = malloc(sizeof(t_point_light_array) + sizeof(t_point_light) * cap);
	if (!alloc)
		return (NULL);
	*alloc = (t_point_light_array){.cap = cap, .len = 0};
	return (alloc);
}
