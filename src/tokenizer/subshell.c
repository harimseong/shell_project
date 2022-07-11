/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 04:01:25 by hseong            #+#    #+#             */
/*   Updated: 2022/07/11 15:25:49 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "parser/token_recognition.h"

int	get_subshell_token(t_iterator *iterator)
{
	int		depth;
	char	target;
	t_dlist	*input_line;

	input_line = iterator->line;
	move_back(input_line);
	target = get_char(input_line->cur);
	depth = 1;
	while (target && depth > 0)
	{
		depth += (target == '(') - (target == ')');
		move_back(input_line);
		target = get_char(input_line->cur);
	}
	if (depth != 0 || input_line->idx == 0)
		return (1);
	return (0);
}
