/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlinkedlist_cur.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:17:56 by hseong            #+#    #+#             */
/*   Updated: 2022/06/09 17:22:53 by gson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "dlinkedlist.h"

void	pop_node(t_dlist *list, t_node *del_node,
		void (*delete_content)(void *))
{
	del_node->next->prev = del_node->prev;
	del_node->prev->next = del_node->next;
	delete_content(del_node->content);
	free(del_node);
	--list->size;
}

void	move_front(t_dlist *list)
{
	if (list->size <= 1 || list->head == list->cur)
		return ;
	list->cur = list->cur->prev;
	--list->idx;
}

void	move_back(t_dlist *list)
{
	if (list->size <= 1 || list->tail == list->cur)
		return ;
	list->cur = list->cur->next;
	++list->idx;
}

void	set_cur(t_dlist *list, void *content)
{
	list->cur->content = content;
}
