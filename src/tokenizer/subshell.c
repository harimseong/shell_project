/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 04:01:25 by hseong            #+#    #+#             */
/*   Updated: 2022/06/21 08:44:49 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "parser/token_recognition.h"

int	get_subshell_token(t_iterator *iterator)
{
	int		depth;
	char	target;

	iterator->line->cur = iterator->line->cur->next;
	erase_at(iterator->line, iterator->line->cur->prev, free);
	depth = 1;
	target = get_char(iterator->line->cur);
	while (target && depth > 0)
	{
		depth += (target == '(') - (target == ')');
		move_back(iterator->line);
		target = get_char(iterator->line->cur);
	}
	erase_at(iterator->line, iterator->line->cur->prev, free);
	--iterator->line->idx;
	if (depth != 0 || iterator->line->idx == 0)
		return (1);
	return (0);
}
