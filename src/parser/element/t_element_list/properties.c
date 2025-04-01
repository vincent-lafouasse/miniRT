/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamar <jamar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:16:00 by jamar             #+#    #+#             */
/*   Updated: 2025/04/01 19:16:01 by jamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./t_element_list.h"
#include <stddef.h>

size_t	el_len(const t_element_list *self)
{
	size_t	i;

	i = 0;
	while (self)
	{
		self = self->next;
		i++;
	}
	return (i);
}
