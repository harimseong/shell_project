/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:22:49 by hseong            #+#    #+#             */
/*   Updated: 2022/05/26 18:16:32 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "dlinkedlist.h"
#include "types.h"
#include "parser/token.h"
#include "parser/parser.h"

static void	parse_pipeline(t_iterator *iterator, t_dlist *pipeline_list);
void	parse_command(t_iterator *iterator, t_dlist *pipeline_list);

t_dlist	*parse(const char *line)
{
	t_iterator	iterator;
	t_dlist		*pipeline_list;
	t_token		*token;

	iterator = (t_iterator){(char *)line, 0};
	pipeline_list = dlist_init();
	push_back(pipeline_list, malloc(t_pipeline));
	parse_pipeline(&iterator, pipeline_list);
	token = token_handler(TOKEN_PEEK);
	while (ft_strcmp(token->word, "&&") == 0
			|| ft_strcmp(token->word, "||"))
	{
		parse_pipeline(&iterator, pipeline_list);
		token = token_handler(TOKEN_PEEK);
	}
	if (token->type != 0)
	{
		parser_error(token);
		return (NULL);
	}
	return (pipeline_list);
}

void	parse_pipeline(t_iterator *iterator, t_dlist *pipeline_list)
{
	t_token		*token;

	parse_command(iterator, pipeline_list);
	token = token_handler(TOKEN_PEEK);
	while (token->type == '|')
	{
		parse_command(iterator, pipeline_list);
		token = token_handler(TOKEN_PEEK);
	}
	if (1)
	{
	}
}

