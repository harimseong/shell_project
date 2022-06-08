/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognition_procedure_1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:59:13 by hseong            #+#    #+#             */
/*   Updated: 2022/06/08 22:15:20 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>

#include "libft.h"
#include "constants.h"
#include "parser/token_recognition.h"

int	check_eoi(t_iterator *iterator, t_token *token, char target)
{
	(void)token;
	(void)iterator;
	if (target == '\0')
	{
		if (check_token_type(token->type, TT_QUOTE_MASK))
			token->type = TT_ERROR;
		return (DELIMIT);
	}
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
	if ((target == '\'' && check_token_type(token->type, TT_SQUOTE))
		|| (target == '"' && check_token_type(token->type, TT_DQUOTE)))
	{
		move_back(iterator->line);
		erase_at(iterator->line, iterator->record, free);
		erase_at(iterator->line, iterator->line->cur->prev, free);
		iterator->line->idx -= 2;
		token->type = TT_WORD;
		return (recog_character(iterator, token));
	}
	else if ((target == '\'' || target == '"')
		&& !check_token_type(token->type, TT_QUOTE_MASK))
	{
		iterator->record = iterator->line->cur;
		if (token->type != TT_EMPTY && !check_token_type(token->type, TT_WORD))
			return (DELIMIT);
		token->type
			|= TT_SQUOTE * (target == '\'') + TT_DQUOTE * (target == '"');
		return (APPLIED);
	}
	return (CONTINUE);
}

int	check_dollar(t_iterator *iterator, t_token *token, char target)
{
	if (target == '$' && !check_token_type(token->type, TT_SQUOTE))
	{
		if (expand_word(iterator))
			return (DELIMIT);
		return (APPLIED);
	}
	return (CONTINUE);
}
