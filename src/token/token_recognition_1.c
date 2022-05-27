/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:36:10 by hseong            #+#    #+#             */
/*   Updated: 2022/05/27 22:54:38 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/token.h"
#include "libft.h"

t_token	*delimit_token(t_iterator *iterator)
{
	t_token		*token;

	(void)iterator;
	token = make_token(NULL, TT_DELIMITER);
	return (token);
}

t_token	*do_nothing(t_iterator *iterator)
{
	t_token		*token;

	(void)iterator;
	token = make_token(NULL, TT_ERROR);
	return (token);
}

t_token	*char_alphabet(t_iterator *iterator)
{
	t_token		*token;

	return (token);
}
