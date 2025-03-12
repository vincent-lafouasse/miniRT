/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_error.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 20:53:20 by poss              #+#    #+#             */
/*   Updated: 2025/02/08 20:57:11 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_ERROR_H
#define T_ERROR_H

typedef enum e_error t_error;
enum e_error {
    NO_ERROR,
    E_LINE_EMPTY,
    E_OOM,
    E_UNREACHABLE,
};

const char* error_repr(t_error err);

#endif
