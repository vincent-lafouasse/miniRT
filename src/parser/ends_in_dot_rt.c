/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ends_in_dot_rt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamar <jamar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:43:50 by jamar             #+#    #+#             */
/*   Updated: 2025/04/01 19:43:50 by jamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"
#include <stdbool.h>
#include <stddef.h>

bool	ends_in_dot_rt(const char *str)
{
	size_t	len;

	len = ft_strlen(str);
	return (len >= 3 && ft_strncmp(&str[len - 3], ".rt", 3) == 0);
}
