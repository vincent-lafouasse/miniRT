#include "t_triangle.h"

#include "math/double/double.h"

t_error triangle_new(t_triangle_specs specs, t_triangle* out) {

	t_vec3 edge1 = vec3_sub(specs.a, specs.b);
	t_vec3 edge2 = vec3_sub(specs.a, specs.c);
	t_vec3 edge3 = vec3_sub(specs.b, specs.c);

	if (
		double_eq(0.0, vec3_length(edge1))
		|| double_eq(0.0, vec3_length(edge2))
		|| double_eq(0.0, vec3_length(edge3))
	) {
		return E_FLAT_TRIANGLE;
	}

	t_vec3 normal = vec3_cross(edge1, edge2);
	double normal_len = vec3_length(normal);
	if (double_eq(0.0, normal_len)) {
		return E_FLAT_TRIANGLE;
	}

	*out = (t_triangle) {
		.a=specs.a, .b=specs.b, .c=specs.c,
		.normal = vec3_div(normal, normal_len),
		.color = specs.color,
	};
	return NO_ERROR;
}
