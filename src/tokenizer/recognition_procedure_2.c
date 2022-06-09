/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognition_procedure_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 22:28:28 by hseong            #+#    #+#             */
/*   Updated: 2022/06/09 16:36:42 by gson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "constants.h"
#include "parser/token_recognition.h"

int	check_new_operator(t_iterator *iterator, t_token *token, char target)
{
	(void)iterator;
	if (!ft_strchr(OPERATOR_LIST, target))
		return (CONTINUE);
	if (token->type != TT_EMPTY)
		return (DELIMIT);
	token->type = get_operator_type(target);
	return (APPLIED);
}

int	check_blank(t_iterator *iterator, t_token *token, char target)
{
	(void)iterator;
	if (!ft_isspace(target))
		return (CONTINUE);
	if (check_token_type(token->type, TT_QUOTE_MASK))
		return (APPLIED);
	return (DELIMIT);
}

int	check_word(t_iterator *iterator, t_token *token, char target)
{
	/*
	char	target;

	target = iterator->line[iterator->end];
	if (is_special(target))
		return (DELIMIT);
	*/
	(void)iterator;
	(void)target;
	if (check_token_type(token->type, TT_WORD))
//		|| check_token_type(token->type, TT_QUOTE_MASK))
		return (APPLIED);
	return (CONTINUE);
}

int	check_new_word(t_iterator *iterator, t_token *token, char target)
{
	/*
	char	target;
target = iterator->line[iterator->end];
	*/
	(void)iterator;
	(void)target;
//	if (check_token_type(token->type, TT_QUOTE_MASK))
//		token->type |= TT_WORD;
	token->type |= TT_WORD;
	return (APPLIED);
}
