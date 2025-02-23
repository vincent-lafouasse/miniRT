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

#define NO_ERROR_REPR "No error"
#define OOM_REPR "Out of memory"
#define UNREACHABLE_REPR "Programming error"

const char* error_repr(t_error err) {
    if (err == NO_ERROR)
        return (NO_ERROR_REPR);
    if (err == E_OOM)
        return (OOM_REPR);
    if (err == E_UNREACHABLE)
        return (UNREACHABLE_REPR);
    return (UNREACHABLE_REPR);
}
