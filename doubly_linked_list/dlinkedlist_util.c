/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlinkedlist_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:20:14 by hseong            #+#    #+#             */
/*   Updated: 2022/05/27 21:22:40 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "dlinkedlist.h"

t_dlist	*dlist_init(void)
{
	t_dlist	*new_list;

	new_list = malloc(sizeof(t_dlist));
	*new_list = (t_dlist){NULL, NULL, NULL, 0, 0, 0};
	return (new_list);
}

void	dlist_local_init(t_dlist *list)
{
	*list = (t_dlist){NULL, NULL, NULL, 0, 0, 0};
}

void	dlist_print_forward(t_dlist *list, void (*print_content)(void *))
{
	t_node	*node;
	size_t	idx;
	size_t	size;

	size = list->size;
	node = list->head;
	idx = 0;
	while (idx < size)
	{
		print_content(node->content);
		node = node->next;
		++idx;
	}
}

void	dlist_print_backward(t_dlist *list, void (*print_content)(void *))
{
	t_node	*node;
	size_t	idx;
	size_t	size;

	size = list->size;
	node = list->tail;
	idx = size;
	while (idx > 0)
	{
		print_content(node->content);
		node = node->prev;
		--idx;
	}
}
