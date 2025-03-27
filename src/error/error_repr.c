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
#define MUST_HAVE_ONE_CAMERA_REPR "Must have one camera"
#define MUST_HAVE_ONE_AMBIENT_LIGHT_REPR "Must have one ambient light"
#define BAD_MAP_SUFFIX_REPR "Map filename must end in \".rt\""
#define NO_POINT_LIGHT_REPR "No point light"
#define VECTOR_NOT_NORMALIZED_REPR "Vector not normalized"
#define OUT_OF_RANGE_REPR "Value out of range"
#define UNEXPECTED_NULL_VECTOR_REPR "Unexpected null vector"
#define BAD_PROGRAM_USAGE_REPR "Bad usage"
#define FLAT_TRIANGLE_REPR "Triangle vertices cannot be colinear"

#define OOM_REPR "Malloc"
#define MLX_INIT_REPR "MLX init"
#define MLX_NEW_WINDOW_REPR "MLX new window"
#define MLX_NEW_IMAGE_REPR "MLX new image"

#define READ_REPR "Read"
#define OPEN_REPR "Open"

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
    if (err == E_MUST_HAVE_ONE_CAMERA)
        return (MUST_HAVE_ONE_CAMERA_REPR);
    if (err == E_MUST_HAVE_ONE_AMBIENT_LIGHT)
        return (MUST_HAVE_ONE_AMBIENT_LIGHT_REPR);
    if (err == E_BAD_MAP_SUFFIX)
        return (BAD_MAP_SUFFIX_REPR);
    if (err == E_NO_POINT_LIGHT)
        return (NO_POINT_LIGHT_REPR);
    if (err == E_OUT_OF_RANGE)
        return (OUT_OF_RANGE_REPR);
    if (err == E_UNEXPECTED_NULL_VECTOR)
        return (UNEXPECTED_NULL_VECTOR_REPR);
    if (err == E_BAD_PROGRAM_USAGE)
        return (BAD_PROGRAM_USAGE_REPR);
    if (err == E_FLAT_TRIANGLE)
        return (FLAT_TRIANGLE_REPR);
    if (err == E_OOM)
        return (OOM_REPR);
    if (err == E_MLX_INIT)
        return (MLX_INIT_REPR);
    if (err == E_MLX_NEW_WINDOW)
        return (MLX_NEW_WINDOW_REPR);
    if (err == E_MLX_NEW_IMAGE)
        return (MLX_NEW_IMAGE_REPR);
    if (err == E_READ)
        return (READ_REPR);
    if (err == E_OPEN)
        return (OPEN_REPR);
    if (err == E_UNREACHABLE)
        return (UNREACHABLE_REPR);
    return (UNKNOWN_VARIANT_REPR);
}
