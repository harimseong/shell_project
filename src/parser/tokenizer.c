/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 21:26:50 by hseong            #+#    #+#             */
/*   Updated: 2022/06/04 23:19:32 by hseong           ###   ########.fr       */
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
static int		check_character(t_iterator *iterator, t_token *token);

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
	char	target;
	char	*line;

	line = iterator->line;
	target = line[iterator->start];
	new_token = ft_calloc(1, sizeof(t_token));
	while (line[iterator->start] != 0)
	{
		iterator->end = iterator->start;
		while (check_character(iterator, new_token) != DELIMIT)
			++iterator->end;
		if (new_token->type != TT_EMPTY)
			break ;
		iterator->start = iterator->end + (iterator->start == iterator->end);
	}
	/*
	if (new_token->type == TT_EMPTY)
	{
		free(new_token);
		return (NULL);
	}
	*/
	if ((new_token->type & TT_DOLLAR) == TT_DOLLAR)
		return (word_expansion(iterator, new_token));
	else
		new_token->word = ft_strndup(line + iterator->start,
			iterator->end - iterator->start);
	return (new_token);
}

int	check_character(t_iterator *iterator, t_token *token)
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
	return (1);
}

/*
t_token	*make_token(char *word, int type)
{
	t_token	*new_token;

	if (type == TT_ERROR)
		return (NULL);
	new_token = malloc(sizeof(t_token));
	new_token->word = word;
	new_token->type = type;
	return (new_token);
}
*/
