#include "./t_element_list.h"

#include <stdlib.h>

void	el_delone(t_element_list **self)
{
	t_element_list	*buffer;

	if (!*self)
		return ;
	buffer = (*self)->next;
	free(*self);
	*self = buffer;
	return ;
}

void	el_clear(t_element_list **self)
{
	while (*self)
		el_delone(self);
}
