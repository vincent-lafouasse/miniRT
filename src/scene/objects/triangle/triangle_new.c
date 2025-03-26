#include "t_triangle.h"

bool double_eq(double, double);

t_error triangle_new(t_point3 a, t_point3 b, t_point3 c, t_rgb color, t_triangle* out) {

	t_vec3 edge1 = vec3_sub(a, b);
	t_vec3 edge2 = vec3_sub(a, c);
	t_vec3 edge3 = vec3_sub(b, c);

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
		.a=a, .b=b, .c=c,
		.normal = vec3_div(normal, normal_len),
		.color = color,
	};
	return NO_ERROR;
}
