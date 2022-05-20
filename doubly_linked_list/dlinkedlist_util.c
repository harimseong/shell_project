/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlinkedlist_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:20:14 by hseong            #+#    #+#             */
/*   Updated: 2022/05/20 21:32:41 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "dlinkedlist.h"

t_dlist	*dlist_init(void)
{
	t_dlist	*list;

	list = malloc(sizeof(t_dlist));
	*list = (t_dlist){NULL, NULL, NULL, 0, 0, 0};
	return (list);
}

void	print_dlist_forward(t_dlist *list, void (*print_content)(void *))
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

void	print_dlist_backward(t_dlist *list, void (*print_content)(void *))
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

void	delete_dlist(t_dlist *list, void (*delete_content)(void *))
{
	empty_dlist(list, delete_content);
	free(list);
}

void	empty_dlist(t_dlist *list, void (*delete_content)(void *))
{
	size_t		size;
	t_node		*trav_node;

	size = list->size;
	if (size == 0)
		return ;
	trav_node = list->head->next;
	while (size > 1)
	{
		delete_content(trav_node->prev->content);
		free(trav_node->prev);
		trav_node = trav_node->next;
		--size;
	}
	free(list->tail);
}
