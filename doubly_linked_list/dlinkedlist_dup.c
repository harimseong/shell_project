/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlinkedlist_dup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 17:25:35 by hseong            #+#    #+#             */
/*   Updated: 2022/02/25 19:39:46 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "dlinkedlist.h"

t_dlist	*duplicate_dlist(t_dlist *list)
{
	t_dlist		*clone;
	size_t		size;
	size_t		idx;

	clone = malloc(sizeof(t_dlist));
	dlist_init(clone);
	size = list->size;
	idx = 0;
	list->cur = list->head;
	while (idx < size)
	{
		push_back(clone, list->cur->item);
		move_back(list);
		++idx;
	}
	list->cur = NULL;
	return (clone);
}
