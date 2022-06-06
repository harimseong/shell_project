/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognition_procedure_1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:59:13 by hseong            #+#    #+#             */
/*   Updated: 2022/06/06 19:46:08 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlinkedlist.h"
#include "libft.h"
#include "constants.h"
#include "parser/token.h"
#include "parser/token_recognition.h"

int	check_eoi(t_iterator *iterator, t_token *token)
{
	(void)token;
	if (get_char(iterator->end) == '\0')
		return (DELIMIT);
	return (CONTINUE);
}

int	check_operator(t_iterator *iterator, t_token *token)
{
	char	target;
	int		type;

	type = token->type;
	target = get_char(iterator->end);
	if ((type & TT_OPERATOR) == TT_OPERATOR)
		return (check_long_operator(target, &token->type));
	return (CONTINUE);
}

/*
 * echo" abc" is treated as "echo abc"
 */
int	check_quote(t_iterator *iterator, t_token *token)
{
	char	target;

	target = get_char(iterator->end);
	if ((target == '\'' && (token->type & TT_SQUOTE) == TT_SQUOTE)
		|| (target == '"' && (token->type & TT_DQUOTE) == TT_DQUOTE))
		return (DELIMIT);
	else if ((target == '\'' && (token->type & TT_SQUOTE) != TT_SQUOTE)
		|| (target == '"' && (token->type & TT_DQUOTE) != TT_DQUOTE))
	{
		if (token->type != TT_EMPTY)
			return (DELIMIT);
		token->type |= TT_QUOTE_MASK;
		token->type &= 0xfffffffc;
		token->type |= (target == '\'') + 2 * (target == '"');
		return (APPLIED);
	}
	return (CONTINUE);
}

int	check_dollar(t_iterator *iterator, t_token *token)
{
	char	target;

	target = get_char(iterator->end);
	if (target == '$' && (token->type & TT_SQUOTE) != TT_SQUOTE)
	{
		// read word(consists of first character _ or alphabet
		//	 and _ or alphabet or number for the rest.
		token->type |= TT_DOLLAR;
		expand_word(iterator);
		return (APPLIED);
	}
	return (CONTINUE);
}
