#include "./t_partitioned_elements.h"

#include "./t_element.h"
#include "./t_element_list/t_element_list.h"

#include "error/t_error.h"

t_error partitioned_elements_push_front(t_partitioned_elements *p, t_element element) {
	t_element_kind kind;

	kind = element.kind;
	if (kind == ELEM_CAMERA)
		return el_push_front(&p->cameras, element);
	else if (kind == ELEM_AMBIENT_LIGHT)
		return el_push_front(&p->ambients, element);
	else if (kind == ELEM_LIGHT)
		return el_push_front(&p->lights, element);
	else if (kind == ELEM_SPHERE_PRIMITIVE || \
			kind == ELEM_PLANE_PRIMITIVE || \
			kind == ELEM_CYLINDER_PRIMITIVE ||
			kind == ELEM_TRIANGLE_PRIMITIVE
		)
		return el_push_front(&p->primitives, element);
	return (E_UNREACHABLE);
}

void partitioned_elements_clear(t_partitioned_elements *p) {
	el_clear(&p->cameras);
	el_clear(&p->ambients);
	el_clear(&p->lights);
	el_clear(&p->primitives);
}
