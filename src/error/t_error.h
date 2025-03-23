/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_error.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 20:53:20 by poss              #+#    #+#             */
/*   Updated: 2025/03/18 19:06:09 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_ERROR_H
#define T_ERROR_H

enum e_error {
    NO_ERROR,

    // input errors
    E_LINE_EMPTY, // non-fatal
    E_UNKNOWN_ELEMENT,
    E_MALFORMATTED_ELEMENT,
    E_MALFORMATTED_COLOR,
    E_MALFORMATTED_VECTOR,
    E_INVALID_NUMBER,
    E_TOO_MANY_CAMERAS,
    E_TOO_MANY_AMBIENT_LIGHTS,
    E_MULTIPLE_LIGHTS_UNSUPPORTED,
    E_VECTOR_NOT_NORMALIZED,
    E_OUT_OF_RANGE,

    // library functions errors
    E_OOM,

    // system call errors
    E_OPEN,
    E_READ,

    // programming errors
    E_UNREACHABLE,
};
typedef enum e_error t_error;

const char* error_repr(t_error err);

#endif
