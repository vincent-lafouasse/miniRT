#include "./t_element_list.h"

#include <stddef.h>

size_t el_len(const t_element_list *self) {
	size_t i;

	i = 0;
	while (self)
	{
		self = self->next;
		i++;
	}
	return (i);
}
