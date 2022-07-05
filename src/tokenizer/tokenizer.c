/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 21:26:50 by hseong            #+#    #+#             */
/*   Updated: 2022/07/01 18:55:30 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

#include "minishell.h"
#include "constants.h"
#include "parser/token_recognition.h"
#include "parser/parser.h"

typedef int	(*t_token_func)(t_iterator *, t_token *);

static t_token	*get_token(t_iterator *iterator);
static void		iterate_buffer(t_iterator *iterator, t_dlist *buf,
				t_token *new_token);

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
	else if (type == TH_END)
		dlist_delete(iterator->line, free);
	return (NULL);
}

t_token	*get_token(t_iterator *iterator)
{
	t_token	*new_token;
	t_dlist	*buf;

	new_token = ft_calloc(1, sizeof(t_token));
	minishell_assert(new_token != NULL, __FILE__, __LINE__);
	buf = iterator->line;
	iterate_buffer(iterator, buf, new_token);
	if (new_token->type == TT_EMPTY)
		return (new_token);
	else if (check_token_type(new_token->type, TT_ASTERISK))
		expand_asterisk(iterator, iterator->line->cur, new_token->type);
	new_token->word = dlist_to_string(buf->head, buf->idx);
	minishell_assert(new_token->word != NULL, __FILE__, __LINE__);
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

void	iterate_buffer(t_iterator *iterator, t_dlist *buf, t_token *new_token)
{
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
}
