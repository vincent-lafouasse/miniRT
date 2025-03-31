/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable_array_new.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 19:03:46 by poss              #+#    #+#             */
/*   Updated: 2025/03/31 19:03:47 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./t_hittable_array.h"
#include <stdlib.h>

t_hittable_array	*hittable_array_new(size_t cap)
{
	t_hittable_array	*alloc;

	alloc = malloc(sizeof(t_hittable_array) + sizeof(t_hittable) * cap);
	if (!alloc)
		return (NULL);
	*alloc = (t_hittable_array){.cap = cap, .len = 0};
	return (alloc);
}
