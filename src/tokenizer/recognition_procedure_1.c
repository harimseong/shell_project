/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognition_procedure_1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:59:13 by hseong            #+#    #+#             */
/*   Updated: 2022/06/07 23:52:18 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>

#include "dlinkedlist.h"
#include "libft.h"
#include "constants.h"
#include "parser/token.h"
#include "parser/token_recognition.h"

int	check_eoi(t_iterator *iterator, t_token *token, char target)
{
	(void)token;
	(void)iterator;
	if (target == '\0')
		return (DELIMIT);
	return (CONTINUE);
}

int	check_operator(t_iterator *iterator, t_token *token, char target)
{
	int		type;

	(void)token;
	(void)iterator;
	type = token->type;
	if ((type & TT_OPERATOR) == TT_OPERATOR)
		return (check_long_operator(target, &token->type));
	return (CONTINUE);
}

/*
 * echo" abc" is treated as "echo abc"
 */
int	check_quote(t_iterator *iterator, t_token *token, char target)
{
	(void)iterator;
	if ((target == '\'' && (token->type & TT_SQUOTE) == TT_SQUOTE)
		|| (target == '"' && (token->type & TT_DQUOTE) == TT_DQUOTE))
	{
		token->type = TT_WORD;
		move_back(iterator->line);
		erase_at(iterator->line, iterator->line->cur->prev, free);
		--iterator->line->idx;
		move_front(iterator->line);
		return (APPLIED);
	}
	else if ((target == '\'' && (token->type & TT_SQUOTE) != TT_SQUOTE)
		|| (target == '"' && (token->type & TT_DQUOTE) != TT_DQUOTE))
	{
		move_back(iterator->line);
		erase_at(iterator->line, iterator->line->cur->prev, free);
		--iterator->line->idx;
		move_front(iterator->line);
		if (token->type != TT_EMPTY && (token->type & TT_WORD) != TT_WORD)
			return (DELIMIT);
		token->type = TT_WORD;
		token->type |= TT_QUOTE_MASK;
		token->type |= (target == '\'') + 2 * (target == '"');
		return (APPLIED);
	}
	return (CONTINUE);
}

int	check_dollar(t_iterator *iterator, t_token *token, char target)
{
	if (target == '$' && (token->type & TT_SQUOTE) != TT_SQUOTE)
	{
		if (expand_word(iterator))
			return (DELIMIT);
		return (APPLIED);
	}
	return (CONTINUE);
}
