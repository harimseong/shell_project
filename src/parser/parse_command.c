/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:58:32 by hseong            #+#    #+#             */
/*   Updated: 2022/05/28 19:31:19 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlinkedlist.h"
#include "libft.h"
#include "types.h"
#include "constants.h"
#include "parser/token.h"
#include "parser/parser.h"

static void	parse_cmd_prefix(t_command *command);
static void	parse_cmd_suffix(t_command *command);
static void	parse_cmd_name(t_command *command);
void		parse_io_redirect(t_dlist *pipeline_list);

void	parse_command(t_command *command)
{
	t_token		*token;

	*command = (t_command){.word_list = dlist_init(),
		.redirect_list = dlist_init()};
	token = token_handler(TH_PEEK, NULL);
	if ((token->type & TT_REDIRECT) == TRUE)
	{
		parse_cmd_prefix(command);
		token = token_handler(TH_PEEK, NULL);
		if (token->type != TT_WORD)
			return ;
	}
	if (token->type == TT_WORD)
	{
		parse_cmd_name(command);
		token = token_handler(TH_PEEK, NULL);
		if ((token->type & TT_REDIRECT) == TRUE || token->type == TT_WORD)
			parse_cmd_suffix(command);
	}
	else
		token->type = TT_ERROR;
}

void	parse_cmd_name(t_command *command)
{
	t_token		*token;

	token = token_handler(TH_GET, NULL);
	push_back(command->word_list, token);
}

void	parse_cmd_prefix(t_command *command)
{
	t_token		*token;

	parse_io_redirect(command->redirect_list);
	token = token_handler(TH_PEEK, NULL);
	while ((token->type & TT_REDIRECT) == TRUE)
	{
		parse_io_redirect(command->redirect_list);
		token = token_handler(TH_PEEK, NULL);
	}
}

void	parse_cmd_suffix(t_command *command)
{
	t_token		*token;

	token = token_handler(TH_PEEK, NULL);
	if ((token->type & TT_REDIRECT) == TRUE)
	{
		parse_io_redirect(command->redirect_list);
		parse_cmd_suffix(command);
	}
	else if (token->type == TT_WORD)
	{
		token = token_handler(TH_GET, NULL);
		push_back(command->word_list, token);
		parse_cmd_suffix(command);
	}
}
