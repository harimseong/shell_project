/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:58:32 by hseong            #+#    #+#             */
/*   Updated: 2022/07/07 21:27:17 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "minishell.h"
#include "constants.h"
#include "parser/parser.h"

static void	parse_cmd_prefix(t_command *command);
static void	parse_cmd_suffix(t_command *command);
static void	parse_cmd_name(t_command *command);
void		parse_io_redirect(t_dlist *pipeline_list, int *flag);

void	parse_simple_command(t_command *command)
{
	t_token		*token;

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
	else
	{
		token->type = TT_ERROR;
		minishell_errormsg(__FILE__, __FUNCTION__, NULL);
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

	parse_io_redirect(command->redirect_list, &command->flag);
	token = token_handler(TH_PEEK, NULL);
	while (check_token_type(token->type, TT_REDIRECT))
	{
		parse_io_redirect(command->redirect_list, &command->flag);
		token = token_handler(TH_PEEK, NULL);
	}
}

void	parse_cmd_suffix(t_command *command)
{
	t_token		*token;

	token = token_handler(TH_PEEK, NULL);
	if (check_token_type(token->type, TT_REDIRECT))
	{
		parse_io_redirect(command->redirect_list, &command->flag);
		parse_cmd_suffix(command);
	}
	else if (check_token_type(token->type, TT_WORD))
	{
		token = token_handler(TH_GET, NULL);
		push_back(command->word_list, token);
		parse_cmd_suffix(command);
	}
}
