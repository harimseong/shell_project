/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlinkedlist_delete.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:58:50 by hseong            #+#    #+#             */
/*   Updated: 2022/06/09 15:59:48 by gson             ###   ########.fr       */
=======
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:58:50 by hseong            #+#    #+#             */
/*   Updated: 2022/06/08 05:43:08 by hseong           ###   ########.fr       */
>>>>>>> upstream/master
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "dlinkedlist.h"

void	dlist_delete(t_dlist *list, void (*delete_content)(void *))
{
	if (list == NULL)
		return ;
	dlist_empty(list, delete_content);
	free(list);
}

void	dlist_empty(t_dlist *list, void (*delete_content)(void *))
{
	size_t		size;
	t_node		*trav_node;

	size = list->size;
	if (size == 0)
		return ;
	trav_node = list->head->next;
	while (size > 1)
	{
		*trav_node->prev = (t_node){NULL, NULL, NULL};
		delete_content(trav_node->prev->content);
		free(trav_node->prev);
		trav_node = trav_node->next;
		--size;
	}
	delete_content(list->tail);
<<<<<<< HEAD
	*list->tail = (t_node){NULL, NULL, NULL};
=======
	*list->tail= (t_node){NULL, NULL, NULL};
>>>>>>> upstream/master
	free(list->tail);
}

void	erase_at(t_dlist *list, t_node *at, void (*delete_content)(void *))
{
	t_node		*trav;

	if (at == list->head)
		pop_front(list, delete_content);
	else if (at == list->tail)
		pop_back(list, delete_content);
	if (at == list->head || at == list->tail)
		return ;
	trav = list->head;
	while (trav && trav != at)
		trav = trav->next;
	if (trav == NULL || trav != at)
		return ;
	at->prev->next = at->next;
	at->next->prev = at->prev;
	delete_content(at->content);
	*at = (t_node){NULL, NULL, NULL};
	free(at);
	--list->size;
}
