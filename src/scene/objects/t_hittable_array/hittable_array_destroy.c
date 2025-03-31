/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable_array_destroy.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 19:03:42 by poss              #+#    #+#             */
/*   Updated: 2025/03/31 19:03:42 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./t_hittable_array.h"
#include <stdlib.h>

void	hittable_array_destroy(t_hittable_array **self)
{
	free(*self);
	*self = NULL;
}
