/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamar <jamar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:26:50 by jamar             #+#    #+#             */
/*   Updated: 2025/04/01 19:26:50 by jamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./t_element_list.h"

#include <stdlib.h>

t_element_list	*el_new(t_element element)
{
	t_element_list	*alloc;

	alloc = malloc(sizeof(*alloc));
	if (!alloc)
		return (NULL);
	*alloc = (t_element_list){.element = element, .next = NULL};
	return (alloc);
}
