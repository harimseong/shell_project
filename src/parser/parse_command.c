/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:58:32 by hseong            #+#    #+#             */
/*   Updated: 2022/05/26 17:14:32 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlinkedlist.h"
#include "types.h"
#include "parser/token.h"
#include "parser/parser.h"
#include <unistd.h>

static void	parse_cmd_prefix(t_iterator *iterator, t_dlist *pipeline_list);
static void	parse_cmd_name(t_iterator *iterator, t_dlist *pipeline_list);

void	parse_command(t_iterator *iterator, t_dlist *pipeline_list)
{
	t_token		*token;

	token = token_handler(TOKEN_PEEK);
	if (token->type == '<' || token->type == '>'
		|| token->type == DGREAT || token->type == DLESS)
		parse_cmd_prefix(iterator, pipeline_list);
	else
		parse_cmd_name(iterator, pipeline_list);
}

void	parse_cmd_prefix(t_iterator *iterator, t_dlist *pipeline_list)
{
	t_token		*token;

	parse_io_redirect(iterator, pipeline_list);
	token = token_handler(TOKEN_PEEK);
	while (token->type == '<' || token->type == '>'
			|| token->type == DLESS || token->type == DGREAT)
	{
		parse_io_redirect(iterator, pipeline_list);
		token = token_handler(TOKEN_PEEK);
	}
}

void	parse_cmd_name(t_iterator *iterator, t_dlist *pipeline_list)
{
	t_token		*token;
	t_node		*node;

	token = token_handler(TOKEN_GET);
	node = pipeline_list->tail;
	node->
}
