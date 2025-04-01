/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamar <jamar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:16:06 by jamar             #+#    #+#             */
/*   Updated: 2025/04/01 19:26:33 by jamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./t_element_list.h"

#include <stddef.h>

void	el_push_front_link(t_element_list **self, t_element_list *link)
{
	t_element_list	*buffer;

	if (!link)
		return ;
	buffer = *self;
	link->next = buffer;
	*self = link;
}

t_error	el_push_front(t_element_list **self, t_element element)
{
	t_element_list	*link;

	link = el_new(element);
	if (!link)
		return (E_OOM);
	el_push_front_link(self, link);
	return (NO_ERROR);
}

t_element_list	*el_pop_front_link(t_element_list **self)
{
	t_element_list	*new_head;
	t_element_list	*link;

	if (!*self)
		return (NULL);
	new_head = (*self)->next;
	link = *self;
	link->next = NULL;
	*self = new_head;
	return (link);
}
