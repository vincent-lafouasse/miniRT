/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamar <jamar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:26:44 by jamar             #+#    #+#             */
/*   Updated: 2025/04/01 19:26:44 by jamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./t_element_list.h"

#include <stdlib.h>

void	el_delone(t_element_list **self)
{
	t_element_list	*buffer;

	if (!*self)
		return ;
	buffer = (*self)->next;
	free(*self);
	*self = buffer;
	return ;
}

void	el_clear(t_element_list **self)
{
	while (*self)
		el_delone(self);
}
