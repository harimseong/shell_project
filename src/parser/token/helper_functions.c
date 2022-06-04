/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 22:23:18 by hseong            #+#    #+#             */
/*   Updated: 2022/06/04 23:15:10 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlinkedlist.h"
#include "libft.h"
#include "parser/token.h"
#include "parser/token_recognition.h"

extern t_dlist	*env_list;

/*
 * if LSB == 2, it's not expandable operator
 * if target is not expandable from previous token, it must be delimited.
 */
int	expand_operator(char target, int type)
{
	if (!(((type == TT_LESS) && target == '<')
		|| ((type == TT_GREAT) && target == '>')))
		return (DELIMIT);
	if (target == '<')
		type = TT_DLESS;
	else if (target == '>')
		type = TT_DGREAT;
	return (APPLIED);
}

void	find_expansion_word(t_iterator *iterator)
{
	char	*line;
	int		idx;

	line = iterator->line;
	idx = iterator->end;
	if (ft_isalpha(line[idx]) == 0 && line[idx] != '_')
		return;
	while (line[idx] && (ft_isalnum(line[idx]) || line[idx] == '_'))
		++idx;
	iterator->end = idx;
}
