/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 21:05:42 by poss              #+#    #+#             */
/*   Updated: 2025/03/29 21:05:42 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_FILE_H
# define READ_FILE_H

# include "./t_string/t_string.h"
# include "error/t_error.h"

# define READ_FILE_BUFFER_SIZE 4096

t_error	read_file(const char *filename, char **output);

#endif // READ_FILE_H
