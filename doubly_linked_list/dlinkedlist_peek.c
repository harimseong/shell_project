/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlinkedlist_peek.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 06:51:51 by hseong            #+#    #+#             */
/*   Updated: 2022/05/11 14:39:46 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlinkedlist.h"

void	peek_front(t_dlist *list, void (*print_item)(t_item *))
{
	if (list->size == 0)
		return ;
	print_item(list->head->item);
}

void	peek_back(t_dlist *list, void (*print_item)(t_item *))
{
	if (list->size == 0)
		return ;
	print_item(list->tail->item);
}

t_item	*get_front(t_dlist *list)
{
	if (list->size == 0)
		return (0);
	return (list->head->item);
}
t_item	*get_back(t_dlist *list)
{
	if (list->size == 0)
		return (0);
	return (list->tail->item);
}
