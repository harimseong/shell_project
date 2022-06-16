/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognition_procedure_1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:59:13 by hseong            #+#    #+#             */
/*   Updated: 2022/06/16 19:14:26 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "constants.h"
#include "parser/token_recognition.h"

int	check_eoi(t_iterator *iterator, t_token *token, char target)
{
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
	(void)iterator;
	if (check_token_type(token->type, TT_OPERATOR))
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
		if (!check_token_type(token->type, TT_EMPTY)
			&& !check_token_type(token->type, TT_WORD))
			return (DELIMIT);
		token->type
			|= TT_SQUOTE * (target == '\'') + TT_DQUOTE * (target == '"');
		return (APPLIED);
	}
	return (CONTINUE);
}

int	check_dollar(t_iterator *iterator, t_token *token, char target)
{
	char	next_target;

	if (target == '$' && !check_token_type(token->type, TT_SQUOTE))
	{
		next_target = get_char(iterator->line->cur->next);
		if (next_target == '\0' || is_ifs(next_target))
			token->type = TT_WORD;
		else if (next_target == '?' || ft_isdigit(next_target))
			special_expansion(iterator, next_target, token->type);
		else if (expand_word(iterator, token->type))
			return (DELIMIT);
		return (check_quote(iterator, token, get_char(iterator->line->cur)));
	}
	return (CONTINUE);
}
