/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_repr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 20:54:19 by poss              #+#    #+#             */
/*   Updated: 2025/02/08 20:56:22 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_error.h"

#define NO_ERROR_REPR "Success"

#define LINE_EMPTY_REPR "Programming error"
#define UNKNOWN_ELEMENT_REPR "Unknown element"
#define MALFORMATTED_ELEMENT_REPR "Malformatted element"
#define MALFORMATTED_COLOR_REPR "Malformatted color"
#define MALFORMATTED_VECTOR_REPR "Malformatted vector"
#define INVALID_NUMBER_REPR "Invalid number"
#define TOO_MANY_CAMERAS_REPR "Too many cameras"
#define TOO_MANY_AMBIENT_LIGHTS_REPR "Too many ambient lights"
#define MULTIPLE_LIGHTS_UNSUPPORTED_REPR "Multiple lights unsupported"
#define VECTOR_NOT_NORMALIZED_REPR "Vector not normalized"
#define OUT_OF_RANGE_REPR "Value out of range"
#define BAD_PROGRAM_USAGE_REPR "Bad usage"

#define OOM_REPR "Malloc"

#define READ_REPR "Read"
#define OPEN_REPR "Read"

#define UNREACHABLE_REPR "Programming error"

#define UNKNOWN_VARIANT_REPR "Unknown error variant"

const char* error_repr(t_error err) {
    if (err == NO_ERROR)
        return NO_ERROR_REPR;
    if (err == E_LINE_EMPTY)
        return (LINE_EMPTY_REPR);
    if (err == E_UNKNOWN_ELEMENT)
        return (UNKNOWN_ELEMENT_REPR);
    if (err == E_MALFORMATTED_ELEMENT)
        return (MALFORMATTED_ELEMENT_REPR);
    if (err == E_MALFORMATTED_COLOR)
        return (MALFORMATTED_COLOR_REPR);
    if (err == E_MALFORMATTED_VECTOR)
        return (MALFORMATTED_VECTOR_REPR);
    if (err == E_INVALID_NUMBER)
        return (INVALID_NUMBER_REPR);
    if (err == E_TOO_MANY_CAMERAS)
        return (TOO_MANY_CAMERAS_REPR);
    if (err == E_TOO_MANY_AMBIENT_LIGHTS)
        return (TOO_MANY_AMBIENT_LIGHTS_REPR);
    if (err == E_MULTIPLE_LIGHTS_UNSUPPORTED)
        return (MULTIPLE_LIGHTS_UNSUPPORTED_REPR);
    if (err == E_OUT_OF_RANGE)
        return (OUT_OF_RANGE_REPR);
    if (err == E_BAD_PROGRAM_USAGE)
        return (BAD_PROGRAM_USAGE_REPR);
    if (err == E_OOM)
        return (OOM_REPR);
    if (err == E_READ)
        return (READ_REPR);
    if (err == E_OPEN)
        return (OPEN_REPR);
    if (err == E_UNREACHABLE)
        return (UNREACHABLE_REPR);
    return (UNKNOWN_VARIANT_REPR);
}
