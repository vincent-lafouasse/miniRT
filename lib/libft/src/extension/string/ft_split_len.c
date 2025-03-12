/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 01:40:55 by poss              #+#    #+#             */
/*   Updated: 2025/03/12 01:41:34 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

size_t	ft_split_len(char *const *split)
{
	size_t	len;

	len = 0;
	while (*split)
	{
		len++;
		split++;
	}
	return (len);
}
