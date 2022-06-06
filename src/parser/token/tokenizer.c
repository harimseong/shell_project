/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 21:26:50 by hseong            #+#    #+#             */
/*   Updated: 2022/06/06 16:18:30 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "dlinkedlist.h"
#include "libft.h"
#include "constants.h"
#include "parser/token.h"
#include "parser/parser.h"
#include "parser/token_recognition.h"

typedef int	(*t_token_func)(t_iterator *, t_token *);

static t_token *get_token(t_iterator *iterator);
static int		recog_character(t_iterator *iterator, t_token *token);

t_token	*token_handler(int type, t_iterator *new_iterator)
{
	static t_iterator	*iterator;
	static t_token		*token;
	t_token				*temp;

	if (new_iterator != NULL && type == TH_SET)
	{
		iterator = new_iterator;
		token = NULL;
		return (NULL);
	}
	else if (type == TH_PEEK)
	{
		if (token == NULL)
			token = get_token(iterator);
		return (token);
	}
	else if (type == TH_GET)
	{
		temp = token;
		token = get_token(iterator);
		return (temp);
	}
	ft_putstr_fd("minishell: token handler flag error\n", STDOUT_FILENO);
	return (NULL);
}

t_token *get_token(t_iterator *iterator)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	while (get_char(iterator->start) != 0)
	{
		iterator->end = iterator->start;
		iterator->len = 0;
		while (recog_character(iterator, new_token))
			iterator->end = iterator->end->next;
		if (new_token->type != TT_EMPTY)
			break ;
		iterator->start = iterator->end;
		if (iterator->len == 0)
			iterator->start = iterator->end->next;
	}
	if (new_token->type == TT_EMPTY)
		return (new_token);
	new_token->word = convert_list(iterator->start, iterator->len);
	iterator->start = iterator->end;
	return (new_token);
}

int	recog_character(t_iterator *iterator, t_token *token)
{
	int		idx;
	int		ret;

	idx = 0;
	ret = CONTINUE;
	while (idx < TABLE_SIZE && ret == CONTINUE)
	{
		ret = g_token_recog_tab[idx](iterator, token);
		++idx;
	}
	if (ret == DELIMIT)
		return (0);
	++iterator->len;
	return (1);
}
