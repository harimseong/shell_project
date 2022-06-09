/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 21:26:50 by hseong            #+#    #+#             */
/*   Updated: 2022/06/09 16:36:22 by gson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"
#include "constants.h"
#include "parser/token_recognition.h"
#include "parser/parser.h"

typedef int	(*t_token_func)(t_iterator *, t_token *);

static t_token	*get_token(t_iterator *iterator);

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
	ft_putstr_fd("minishell: token handler error\n", STDERR_FILENO);
	return (NULL);
}

t_token	*get_token(t_iterator *iterator)
{
	t_token	*new_token;
	t_dlist	*buf;

	new_token = ft_calloc(1, sizeof(t_token));
	buf = iterator->line;
	while (get_char(buf->head) != 0)
	{
		buf->cur = buf->head;
		buf->idx = 0;
		while (recog_character(iterator, new_token) != DELIMIT)
			move_back(buf);
		if (new_token->type != TT_EMPTY)
			break ;
		while (buf->size > 0 && buf->head != buf->cur)
			pop_front(buf, free);
		if (buf->idx == 0)
			pop_front(buf, free);
	}
	if (new_token->type == TT_EMPTY)
		return (new_token);
	new_token->word = convert_list(buf->head, buf->idx);
	while (buf->size > 0 && buf->head != buf->cur)
		pop_front(buf, free);
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
		ret = g_token_recog_tab[idx](iterator, token,
				get_char(iterator->line->cur));
		++idx;
	}
	iterator->len += ret != DELIMIT;
	++iterator->len;
	return (ret);
}
