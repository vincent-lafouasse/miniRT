/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_properties.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamar <jamar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:30:58 by jamar             #+#    #+#             */
/*   Updated: 2025/04/01 19:30:58 by jamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lenient.h"
#include "./t_element.h"
#include "error/t_error.h"
#include <stddef.h>

t_error	u8_parse(const char *str, uint8_t *result_out);
t_error	double_parse(const char *str, double *result_out);

t_error	element_vec3_parse(const char *str, t_vec3 *result_out);
t_error	element_color_parse(const char *str, uint8_t result_out[3]);

t_error	match_ambient_light(char *const *parts, size_t parts_len,
		t_element *element_out)
{
	t_error					err;
	t_ambient_light_element	ambient;

	if (parts_len < 3)
		return (E_MALFORMATTED_ELEMENT);
	if (!LENIENT_PARSER && parts_len > 3)
		return (E_MALFORMATTED_ELEMENT);
	ambient = (typeof(ambient)){0};
	err = double_parse(parts[1], &ambient.lighting_ratio);
	if (err != NO_ERROR)
		return (err);
	err = element_color_parse(parts[2], ambient.color);
	if (err != NO_ERROR)
		return (err);
	*element_out = (t_element){.kind = ELEM_AMBIENT_LIGHT, .ambient = ambient};
	return (NO_ERROR);
}

t_error	match_camera(char *const *parts, size_t parts_len,
		t_element *element_out)
{
	t_error				err;
	t_camera_element	camera;

	if (parts_len < 4)
		return (E_MALFORMATTED_ELEMENT);
	if (!LENIENT_PARSER && parts_len > 4)
		return (E_MALFORMATTED_ELEMENT);
	camera = (typeof(camera)){0};
	err = element_vec3_parse(parts[1], &camera.coordinates);
	if (err != NO_ERROR)
		return (err);
	err = element_vec3_parse(parts[2], &camera.orientation);
	if (err != NO_ERROR)
		return (err);
	err = u8_parse(parts[3], &camera.fov);
	if (err != NO_ERROR)
		return (err);
	*element_out = (t_element){.kind = ELEM_CAMERA, .camera = camera};
	return (NO_ERROR);
}

t_error	match_light(char *const *parts, size_t parts_len,
		t_element *element_out)
{
	t_error			err;
	t_light_element	light;

	if (parts_len < 4)
		return (E_MALFORMATTED_ELEMENT);
	if (!LENIENT_PARSER && parts_len > 4)
		return (E_MALFORMATTED_ELEMENT);
	light = (typeof(light)){0};
	err = element_vec3_parse(parts[1], &light.coordinates);
	if (err != NO_ERROR)
		return (err);
	err = double_parse(parts[2], &light.brightness_ratio);
	if (err != NO_ERROR)
		return (err);
	err = element_color_parse(parts[3], light.color);
	if (err != NO_ERROR)
		return (err);
	*element_out = (t_element){.kind = ELEM_LIGHT, .light = light};
	return (NO_ERROR);
}
