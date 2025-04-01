/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_property_parse.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamar <jamar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:17:36 by jamar             #+#    #+#             */
/*   Updated: 2025/04/01 19:17:36 by jamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error/t_error.h"
#include "libft/ft_string.h"
#include "math/t_vec3/t_vec3.h"
#include <stdint.h>

t_error	u8_parse(const char *str, uint8_t *result_out);
t_error	double_parse(const char *str, double *result_out);

t_error	element_vec3_parse(const char *str, t_vec3 *result_out)
{
	char	**components;
	t_error	x_err;
	t_error	y_err;
	t_error	z_err;

	components = ft_split(str, ',');
	if (!components)
		return (E_OOM);
	if (ft_split_len(components) != 3)
		return (E_MALFORMATTED_VECTOR);
	x_err = double_parse(components[0], &result_out->x);
	y_err = double_parse(components[1], &result_out->y);
	z_err = double_parse(components[2], &result_out->z);
	ft_split_destroy(components);
	if (x_err != NO_ERROR)
		return (x_err);
	if (y_err != NO_ERROR)
		return (y_err);
	if (z_err != NO_ERROR)
		return (z_err);
	return (NO_ERROR);
}

t_error	element_color_parse(const char *str, uint8_t result_out[3])
{
	char	**bytes;
	t_error	r_err;
	t_error	g_err;
	t_error	b_err;

	bytes = ft_split(str, ',');
	if (!bytes)
		return (E_OOM);
	if (ft_split_len(bytes) != 3)
		return (E_MALFORMATTED_COLOR);
	r_err = u8_parse(bytes[0], &result_out[0]);
	g_err = u8_parse(bytes[1], &result_out[1]);
	b_err = u8_parse(bytes[2], &result_out[2]);
	ft_split_destroy(bytes);
	if (r_err != NO_ERROR)
		return (r_err);
	if (g_err != NO_ERROR)
		return (g_err);
	if (b_err != NO_ERROR)
		return (b_err);
	return (NO_ERROR);
}
