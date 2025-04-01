/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamar <jamar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:42:38 by jamar             #+#    #+#             */
/*   Updated: 2025/04/01 19:42:42 by jamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "camera/t_camera.h"
# include "error/t_error.h"
# include "scene/t_scene.h"

t_error	parse_from_file(const char *filname, t_camera_specs *cam_out,
			t_scene *scene_out);
t_error	parse(const char *input, t_camera_specs *cam_out, t_scene *scene_out);

#endif // PARSE_H
