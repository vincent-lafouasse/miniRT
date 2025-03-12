#ifndef T_ELEMENT_LIST_H
# define T_ELEMENT_LIST_H

#include "./t_element.h"

#include "error/t_error.h"

typedef struct s_element_list	t_element_list;
struct s_element_list {
	t_element		element;
	t_element_list	*next;
};

#include <stdlib.h>
static inline t_element_list *el_new(t_element element) {
	t_element_list *alloc;

	alloc = malloc(sizeof(*alloc));
	if (!alloc)
		return (NULL);
	*alloc = (t_element_list){.element = element, .next = NULL};
	return (alloc);
}

static inline void	el_push_front_link(t_element_list **self, t_element_list *link) {
	t_element_list *buffer;

	if (!link)
		return ;
	buffer = *self;
	link->next = buffer;
	*self = link;
}

static inline t_error el_push_front(t_element_list **self, t_element element) {
	t_element_list *link;

	link = el_new(element);
	if (!link)
		return (E_OOM);
	el_push_front_link(self, link);
	return (NO_ERROR);
}

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

#endif // T_ELEMENT_LIST_H
