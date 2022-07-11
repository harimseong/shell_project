/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 21:26:50 by hseong            #+#    #+#             */
/*   Updated: 2022/07/11 15:35:47 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "dlinkedlist.h"

#include "minishell.h"
#include "constants.h"
#include "parser/token_recognition.h"
#include "parser/parser.h"

typedef int	(*t_token_func)(t_iterator *, t_token *);

static t_token	*get_token(t_iterator *iterator);
static void		iterate_buffer(t_iterator *iterator, t_dlist *buf,
				t_token *new_token);
static void		postprocess_token(t_iterator *iterator, t_token *new_token);

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
	return (ret);
}

static t_token	*get_token(t_iterator *iterator)
{
	t_token	*new_token;
	t_dlist	*input_line;

	new_token = ft_calloc(1, sizeof(t_token));
	minishell_assert(new_token != NULL, __FILE__, __LINE__);
	input_line = iterator->line;
	iterate_buffer(iterator, input_line, new_token);
	if (new_token->type == TT_EMPTY)
		return (new_token);
	postprocess_token(iterator, new_token);
	new_token->word = dlist_to_string(input_line->head, input_line->idx);
	minishell_assert(new_token->word != NULL, __FILE__, __LINE__);
	while (input_line->size > 0 && input_line->head != input_line->cur)
		pop_front(input_line, free);
	return (new_token);
}

static void	iterate_buffer(t_iterator *iterator, t_dlist *input_line,
		t_token *new_token)
{
	while (get_char(input_line->head) != 0)
	{
		input_line->cur = input_line->head;
		input_line->idx = 0;
		while (recog_character(iterator, new_token) != DELIMIT)
			move_back(input_line);
		if (new_token->type != TT_EMPTY)
			break ;
		while (input_line->size > 0 && input_line->head != input_line->cur)
			pop_front(input_line, free);
		if (input_line->idx == 0)
			pop_front(input_line, free);
	}
}

static void		postprocess_token(t_iterator *iterator, t_token *new_token)
{
	t_dlist		*input_line;

	input_line = iterator->line;
	if (check_token_type(new_token->type, TT_ASTERISK))
	{
		expand_asterisk(iterator, input_line->cur, new_token->type);
		iterate_buffer(iterator, input_line, new_token);
	}
	else if (check_token_type(new_token->type, TT_PARENTHESIS))
	{
		erase_at(input_line, input_line->head, free);
		erase_at(input_line, input_line->cur->prev, free);
		input_line->idx -= 2;
	}
}
