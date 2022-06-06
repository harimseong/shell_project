/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlinkedlist_transfer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 14:07:35 by hseong            #+#    #+#             */
/*   Updated: 2022/06/05 15:23:45 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "dlinkedlist.h"

void	dlist_transfer_arr(t_dlist *list, const void *arr, size_t size, size_t count)
{
	void	*unit;
	size_t	idx;

	idx = 0;
	while (idx < count)
	{
		unit = malloc(size);
		ft_memcpy(unit, arr + size * idx, size);
		push_back(list, unit);
		++idx;
	}
}

t_dlist	*dlist_init_arr(const void *arr, size_t size, size_t count)
{
	t_dlist	*list;
	void	*unit;
	size_t	idx;

	list = dlist_init();
	idx = 0;
	while (idx < count)
	{
		unit = malloc(size);
		ft_memcpy(unit, arr + size * idx, size);
		push_back(list, unit);
		++idx;
	}
	return (list);
}
