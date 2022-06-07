/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 22:23:18 by hseong            #+#    #+#             */
/*   Updated: 2022/06/07 14:18:07 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlinkedlist.h"
#include "libft.h"
#include "parser/token.h"
#include "parser/token_recognition.h"

/*
 * if LSB == 2, it's not expandable operator
 * if target is not expandable from previous token, it must be delimited.
 */
int	is_operator(char target)
{
	if (target == '<' || target == '>'
		|| target == '|' || target == '$'
		|| target == '\'' || target == '"')
		return (1);
	return (0);
}

int	check_long_operator(char target, int *type)
{
	if (!(((*type == TT_LESS) && target == '<')
		|| ((*type == TT_GREAT) && target == '>')))
		return (DELIMIT);
	if (target == '<')
		*type = TT_DLESS;
	else if (target == '>')
		*type = TT_DGREAT;
	return (APPLIED);
}

char	get_char(t_node *node)
{
	if (node == NULL)
		return ('\0');
	return (*(char *)node->content);
}

char	*convert_list(t_node *node, size_t len)
{
	char	*word;
	size_t	idx;

	word = malloc(len + 1);
	word[len] = 0;
//	if (word == NULL)
//		return (NULL);
	idx = 0;
	while (node && idx < len)
	{
		word[idx] = get_char(node);
		++idx;
		node = node->next;
	}
	return (word);
}

int	get_operator_type(char target)
{
	if (target == '<')
		return (TT_LESS);
	else if (target == '>')
		return (TT_GREAT);
	else if (target == '|')
		return (TT_PIPE);
	return (0);
}

