#ifndef T_PARTITIONED_ELEMENTS_H
#define T_PARTITIONED_ELEMENTS_H

#include "./t_element.h"
#include "./t_element_list/t_element_list.h"

#include "error/t_error.h"

typedef struct s_partitioned_elements {
	t_element_list *cameras;
	t_element_list *ambients;
	t_element_list *lights;
	t_element_list *primitives;
} t_partitioned_elements;

t_error partitioned_elements_push_front(t_partitioned_elements *p, t_element element);
void partitioned_elements_clear(t_partitioned_elements *p);

#endif // T_PARTITIONED_ELEMENTS_H
