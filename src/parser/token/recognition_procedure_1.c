/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognition_procedure_1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:59:13 by hseong            #+#    #+#             */
/*   Updated: 2022/06/03 21:57:45 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "constants.h"
#include "parser/token.h"
#include "parser/token_recognition.h"

static int	expand_operator(char target, int type);

int	check_eoi(t_iterator *iterator, t_token *token)
{
	(void)token;
	if (iterator->line[iterator->end] == '\0')
		return (DELIMIT);
	return (CONTINUE);
}

int	check_operator(t_iterator *iterator, t_token *token)
{
	char	target;
	int		type;

	type = token->type;
	target = iterator->line[iterator->end] == '\0';
	if ((type & TT_OPERATOR) == TT_OPERATOR)
		return (expand_operator(target, type));
	return (CONTINUE);
}

/*
 * echo" abc" is treated as "echo abc"
 */
int	check_quote(t_iterator *iterator, t_token *token)
{
	char	target;

	target = iterator->line[iterator->end];
	if ((target == '\'' && (token->type & TT_SQUOTE) == TT_SQUOTE)
		|| (target == '"' && (token->type & TT_DQUOTE) == TT_DQUOTE))
		return (DELIMIT);
	else if ((target == '\'' && (token->type & TT_SQUOTE) != TT_SQUOTE)
		|| (target == '"' && (token->type & TT_DQUOTE) != TT_DQUOTE))
	{
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

	target = iterator->line[iterator->end];
	if (target == '$')
		
}

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
