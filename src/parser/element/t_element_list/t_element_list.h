#ifndef T_ELEMENT_LIST_H
# define T_ELEMENT_LIST_H

#include "../t_element.h"

#include "error/t_error.h"

#include <stddef.h>

typedef struct s_element_list	t_element_list;
struct s_element_list {
	t_element		element;
	t_element_list	*next;
};

t_element_list *el_new(t_element element);

void	el_push_front_link(t_element_list **self, t_element_list *link);
t_error el_push_front(t_element_list **self, t_element element);
t_element_list *el_pop_front_link(t_element_list **self);

size_t el_len(const t_element_list *self);

void	el_delone(t_element_list **self);
void	el_clear(t_element_list **self);

#endif // T_ELEMENT_LIST_H
