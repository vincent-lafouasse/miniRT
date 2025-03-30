/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_light_array_destroy.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 01:06:12 by poss              #+#    #+#             */
/*   Updated: 2025/03/30 01:06:14 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./t_point_light_array.h"
#include <stdlib.h>

void	point_light_array_destroy(t_point_light_array **self)
{
	free(*self);
	*self = NULL;
}
