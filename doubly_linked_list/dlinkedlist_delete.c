/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlinkedlist_delete.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:58:50 by hseong            #+#    #+#             */
/*   Updated: 2022/05/26 20:59:21 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "dlinkedlist.h"

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
