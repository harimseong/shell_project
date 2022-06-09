/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:58:32 by hseong            #+#    #+#             */
/*   Updated: 2022/06/08 22:19:36 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft.h"
#include "types.h"
#include "constants.h"
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
	if (check_token_type(token->type, TT_REDIRECT))
	{
		parse_cmd_prefix(command);
		token = token_handler(TH_PEEK, NULL);
		if (token->type != TT_WORD)
			return ;
	}
	if (check_token_type(token->type, TT_WORD))
	{
		parse_cmd_name(command);
		token = token_handler(TH_PEEK, NULL);
		if (check_token_type(token->type, TT_REDIRECT)
			|| check_token_type(token->type, TT_WORD))
			parse_cmd_suffix(command);
	}
	else if (check_token_type(token->type, TT_PIPE))
		return ;
	else
	{
		if (DEBUG_FLAG)
			printf("minishell: parse error: %s: %s: %d: token_type %x\n",
				__FILE__, __FUNCTION__, __LINE__, token->type);
		token->type = TT_ERROR;
	}
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
	while (check_token_type(token->type, TT_REDIRECT))
	{
		parse_io_redirect(command->redirect_list);
		token = token_handler(TH_PEEK, NULL);
	}
}

void	parse_cmd_suffix(t_command *command)
{
	t_token		*token;

	token = token_handler(TH_PEEK, NULL);
	if (check_token_type(token->type, TT_REDIRECT))
	{
		parse_io_redirect(command->redirect_list);
		parse_cmd_suffix(command);
	}
	else if (check_token_type(token->type, TT_WORD))
	{
		token = token_handler(TH_GET, NULL);
		push_back(command->word_list, token);
		parse_cmd_suffix(command);
	}
}
