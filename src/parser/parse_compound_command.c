/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_compound_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 06:57:35 by hseong            #+#    #+#             */
/*   Updated: 2022/06/21 09:10:13 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "minishell.h"
#include "parser/parser.h"
#include "parser/token.h"

void		parse_io_redirect(t_dlist *redirect_list, int *flag);
static void	parse_subshell(t_command *command);
static void	parse_redirect_list(t_command *command);

/*
 * TT_PAREN_OPEN has been checked both in here and parse_command.
 * adding is_compound_command at parse_command would be better.
 */
void	parse_compound_command(t_command *command)
{
	t_token		*token;

	token = token_handler(TH_PEEK, NULL);
	if (check_token_type(token->type, TT_PAREN_OPEN))
		parse_subshell(command);
	token = token_handler(TH_PEEK, NULL);
	if (check_token_type(token->type, TT_REDIRECT))
		parse_redirect_list(command);
}

void	parse_subshell(t_command *command)
{
	t_token		*token;
	t_token		*argv_token;
	t_dlist		*word_list;

	token = token_handler(TH_GET, NULL);
	word_list = command->word_list;
	argv_token = ft_calloc(1, sizeof(t_token));
	*argv_token = (t_token){ft_strndup(get_argv(NULL)[0],
			ft_strlen(get_argv(NULL)[0])), TT_WORD};
	push_back(word_list, argv_token);
	argv_token = ft_calloc(1, sizeof(t_token));
	*argv_token = (t_token){ft_strndup("-c", 2), TT_WORD};
	push_back(word_list, argv_token);
	push_back(word_list, token);
}

/*
 * same as parse_cmd_prefix
 */
void	parse_redirect_list(t_command *command)
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
