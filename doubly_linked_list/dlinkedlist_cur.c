/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlinkedlist_cur.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:17:56 by hseong            #+#    #+#             */
/*   Updated: 2022/05/20 21:30:14 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlinkedlist.h"

void	move_front(t_dlist *list)
{
	if (list->cur == list->head)
		return ;
	list->cur = list->cur->prev;
	--list->idx;
}

void	move_back(t_dlist *list)
{
	if (list->cur == list->tail)
		return ;
	list->cur = list->cur->next;
	++list->idx;
}

void	set_cur(t_dlist *list, void *content)
{
	list->cur->content = content;
}
