/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:36:10 by hseong            #+#    #+#             */
/*   Updated: 2022/05/28 21:24:30 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "parser/token.h"
#include "libft.h"

t_token	*char_delimiter(t_iterator *iterator)
{
	t_token		*token;
	char		target;

	target = iterator->line[++iterator->pos];
	while (target && ft_isspace(target) == TRUE)
		target = iterator->line[++iterator->pos];
	return (g_token_tab[target](iterator));
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
