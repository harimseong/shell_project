/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognition_procedure_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 22:28:28 by hseong            #+#    #+#             */
/*   Updated: 2022/07/01 18:59:24 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "constants.h"
#include "parser/token.h"
#include "parser/token_recognition.h"

#define OPERATOR_LIST ("<>|&()")

int	check_new_operator(t_iterator *iterator, t_token *token, char target)
{
	if (!ft_strchr(OPERATOR_LIST, target))
		return (CONTINUE);
	if (check_token_type(token->type, TT_QUOTE_MASK))
		return (APPLIED);
	if (!check_token_type(token->type, TT_EMPTY))
		return (DELIMIT);
	token->type = get_operator_type(target);
	if (check_token_type(token->type, TT_PARENTHESIS))
	{
		if (check_token_type(token->type, TT_PAREN_CLOSE)
			|| get_subshell_token(iterator))
			token->type = TT_ERROR;
		return (DELIMIT);
	}
	return (APPLIED);
}

int	check_blank(t_iterator *iterator, t_token *token, char target)
{
	(void)iterator;
	if (!is_ifs(target))
		return (CONTINUE);
	if (check_token_type(token->type, TT_QUOTE_MASK))
		return (APPLIED);
	return (DELIMIT);
}

int	check_word(t_iterator *iterator, t_token *token, char target)
{
	if (check_token_type(token->type, TT_WORD))
	{
		if (!check_token_type(token->type, TT_QUOTE_MASK) && target == '*')
			token->type |= TT_ASTERISK;
		return (APPLIED);
	}
	return (CONTINUE);
}

int	check_new_word(t_iterator *iterator, t_token *token, char target)
{
	if (target == '~')
		special_expansion(iterator, target, token->type);
	token->type |= TT_WORD;
	return (APPLIED);
}
