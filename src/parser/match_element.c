#include "./t_element.h"

#include "error/t_error.h"

#include "libft/string.h"
#include "libft/ft_string.h"

#include <stddef.h>

t_error match_ambient_light(char *const *parts, size_t parts_len, t_element *element_out);
t_error match_camera(char *const *parts, size_t parts_len, t_element *element_out);
t_error match_light(char *const *parts, size_t parts_len, t_element *element_out);
t_error match_sphere(char *const *parts, size_t parts_len, t_element *element_out);
t_error match_plane(char *const *parts, size_t parts_len, t_element *element_out);
t_error match_cylinder(char *const *parts, size_t parts_len, t_element *element_out);

t_error	u8_parse(const char *str, uint8_t *result_out);
t_error double_parse(const char *str, double *result_out);

t_error element_vec3_parse(const char *str, t_vec3 *result_out);
t_error element_color_parse(const char *str, uint8_t result_out[3]);

static char ft_strcmp(const char *s1, const char *s2) {
	return ft_strncmp(s1, s2, ft_strlen(s1) + 1);
}

t_error match_element(const char *line, t_element *element_out)
{
	char	**parts;
	size_t	parts_len;
	t_error	err;

	parts = ft_split_charset(line, " \t\v\n\r\f");
	if (!parts)
		return (E_OOM);
	parts_len = ft_split_len(parts);
	if (parts_len == 0)
	{
		ft_split_destroy(parts);
		return (E_LINE_EMPTY);
	}

	if (0 == ft_strcmp(parts[0], TAG_AMBIENT_LIGHT))
		err = match_ambient_light(parts, parts_len, element_out);
	else if (0 == ft_strcmp(parts[0], TAG_CAMERA))
		err = match_camera(parts, parts_len, element_out);
	else if (0 == ft_strcmp(parts[0], TAG_LIGHT))
		err = match_light(parts, parts_len, element_out);
	else if (0 == ft_strcmp(parts[0], TAG_SPHERE))
		err = match_sphere(parts, parts_len, element_out);
	else if (0 == ft_strcmp(parts[0], TAG_PLANE))
		err = match_plane(parts, parts_len, element_out);
	else if (0 == ft_strcmp(parts[0], TAG_CYLINDER))
		err = match_cylinder(parts, parts_len, element_out);
	else
		err = E_UNKNOWN_ELEMENT;

	ft_split_destroy(parts);
	return (err);
}

t_error match_ambient_light(char *const *parts, size_t parts_len, t_element *element_out)
{
	t_error err;
	t_ambient_light_element ambient;

	if (parts_len != 3)
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

t_error match_camera(char *const *parts, size_t parts_len, t_element *element_out)
{
	t_error err;
	t_camera_element camera;

	if (parts_len != 4)
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

t_error match_light(char *const *parts, size_t parts_len, t_element *element_out)
{
	t_error err;
	t_light_element light;

	if (parts_len != 4)
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

t_error match_sphere(char *const *parts, size_t parts_len, t_element *element_out)
{
	t_error err;
	t_sphere_element sphere;

	if (parts_len != 4)
		return (E_MALFORMATTED_ELEMENT);

	sphere = (typeof(sphere)){0};
	err = element_vec3_parse(parts[1], &sphere.center);
	if (err != NO_ERROR)
		return (err);
	err = double_parse(parts[2], &sphere.diameter);
	if (err != NO_ERROR)
		return (err);
	err = element_color_parse(parts[3], sphere.color);
	if (err != NO_ERROR)
		return (err);
	*element_out = (t_element){.kind = ELEM_SPHERE_PRIMITIVE, .sphere = sphere};
	return (NO_ERROR);
}

t_error match_plane(char *const *parts, size_t parts_len, t_element *element_out)
{
	t_error err;
	t_plane_element plane;

	if (parts_len != 4)
		return (E_MALFORMATTED_ELEMENT);

	plane = (typeof(plane)){0};
	err = element_vec3_parse(parts[1], &plane.point);
	if (err != NO_ERROR)
		return (err);
	err = element_vec3_parse(parts[2], &plane.normal);
	if (err != NO_ERROR)
		return (err);
	err = element_color_parse(parts[3], plane.color);
	if (err != NO_ERROR)
		return (err);
	*element_out = (t_element){.kind = ELEM_PLANE_PRIMITIVE, .plane = plane};
	return (NO_ERROR);
}

t_error match_cylinder(char *const *parts, size_t parts_len, t_element *element_out)
{
	t_error err;
	t_cylinder_element cylinder;

	if (parts_len != 6)
		return (E_MALFORMATTED_ELEMENT);

	cylinder = (typeof(cylinder)){0};
	err = element_vec3_parse(parts[1], &cylinder.point);
	if (err != NO_ERROR)
		return (err);
	err = element_vec3_parse(parts[2], &cylinder.axis);
	if (err != NO_ERROR)
		return (err);
	err = double_parse(parts[3], &cylinder.diameter);
	if (err != NO_ERROR)
		return (err);
	err = double_parse(parts[4], &cylinder.height);
	if (err != NO_ERROR)
		return (err);
	err = element_color_parse(parts[5], cylinder.color);
	if (err != NO_ERROR)
		return (err);
	*element_out = (t_element){.kind = ELEM_CYLINDER_PRIMITIVE, .cylinder = cylinder};
	return (NO_ERROR);
}
