#include "./t_element.h"
#include "../lenient.h"

#include "error/t_error.h"

#include <stddef.h>

t_error	u8_parse(const char *str, uint8_t *result_out);
t_error double_parse(const char *str, double *result_out);

t_error element_vec3_parse(const char *str, t_vec3 *result_out);
t_error element_color_parse(const char *str, uint8_t result_out[3]);

t_error match_sphere(char *const *parts, size_t parts_len, t_element *element_out)
{
	t_error err;
	t_sphere_element sphere;

	if (parts_len < 4)
		return (E_MALFORMATTED_ELEMENT);
	if (!LENIENT_PARSER && parts_len > 4)
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

	if (parts_len < 4)
		return (E_MALFORMATTED_ELEMENT);
	if (!LENIENT_PARSER && parts_len > 4)
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

	if (parts_len < 6)
		return (E_MALFORMATTED_ELEMENT);
	if (!LENIENT_PARSER && parts_len > 6)
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

t_error match_triangle(char *const *parts, size_t parts_len, t_element *element_out)
{
	t_error err;
	t_triangle_element triangle;

	if (parts_len < 5)
		return (E_MALFORMATTED_ELEMENT);
	if (!LENIENT_PARSER && parts_len > 5)
		return (E_MALFORMATTED_ELEMENT);

	triangle = (typeof(triangle)){0};
	err = element_vec3_parse(parts[1], &triangle.a);
	if (err != NO_ERROR)
		return (err);
	err = element_vec3_parse(parts[2], &triangle.b);
	if (err != NO_ERROR)
		return (err);
	err = element_vec3_parse(parts[3], &triangle.c);
	if (err != NO_ERROR)
		return (err);
	err = element_color_parse(parts[4], triangle.color);
	if (err != NO_ERROR)
		return (err);
	*element_out = (t_element){.kind = ELEM_TRIANGLE_PRIMITIVE, .triangle = triangle};
	return (NO_ERROR);
}
