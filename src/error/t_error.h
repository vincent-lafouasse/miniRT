/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_error.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 20:53:20 by poss              #+#    #+#             */
/*   Updated: 2025/03/30 00:41:58 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_ERROR_H
# define T_ERROR_H

enum	e_error
{
	NO_ERROR,
	E_LINE_EMPTY,
	E_UNKNOWN_ELEMENT,
	E_MALFORMATTED_ELEMENT,
	E_MALFORMATTED_COLOR,
	E_MALFORMATTED_VECTOR,
	E_INVALID_NUMBER,
	E_MUST_HAVE_ONE_CAMERA,
	E_MUST_HAVE_ONE_AMBIENT_LIGHT,
	E_NO_POINT_LIGHT,
	E_OUT_OF_RANGE,
	E_UNEXPECTED_NULL_VECTOR,
	E_BAD_PROGRAM_USAGE,
	E_BAD_MAP_SUFFIX,
	E_FLAT_TRIANGLE,
	E_OOM,
	E_MLX_INIT,
	E_MLX_NEW_WINDOW,
	E_MLX_NEW_IMAGE,
	E_OPEN,
	E_READ,
	E_UNREACHABLE,
};
typedef enum e_error	t_error;

const char	*error_repr(t_error err);

#endif
