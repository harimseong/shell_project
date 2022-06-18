/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:22:49 by hseong            #+#    #+#             */
/*   Updated: 2022/06/18 17:12:34 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "readline/readline.h"
#include "readline/history.h"
#include "libft.h"

#include "minishell.h"
#include "cmd.h"
#include "constants.h"
#include "parser/parser.h"
#include "parser/token_recognition.h"

#define PARSE_ERROR_STATUS (255)

extern t_dlist	*g_env_list;

void			parse_command(t_command *command);
static void		parse_pipeline(t_pipeline *pipeline);
static t_dlist	*parse_init(t_dlist *pipeline_list);

t_dlist	*parser(const char *line, t_dlist *env_list)
{
	t_dlist		*dlist_line;
	t_token		*token;
	t_iterator	iterator;

	dlist_line = array_to_dlist_init(line, sizeof(char), ft_strlen(line) + 1);
	iterator = (t_iterator){NULL, dlist_line, 0, env_list};
	token_handler(TH_SET, &iterator);
	token = token_handler(TH_PEEK, NULL);
	if (check_token_type(token->type, TT_EMPTY))
	{
		set_question(g_env_list, 0);
		delete_word_content(token);
		token_handler(TH_END, NULL);
		return (NULL);
	}
	return (parse_init(dlist_init()));
}

t_dlist	*parse_init(t_dlist *pipeline_list)
{
	t_token		*token;

	push_back(pipeline_list, ft_calloc(1, sizeof(t_pipeline)));
	parse_pipeline(pipeline_list->head->content);
	token = token_handler(TH_PEEK, NULL);
	while (check_token_type(token->type, TT_PIPELINE))
	{
		((t_pipeline *)get_back(pipeline_list))->pipeline_type = token->type;
		delete_word_content(token_handler(TH_GET, NULL));
		push_back(pipeline_list, ft_calloc(1, sizeof(t_pipeline)));
		parse_pipeline(pipeline_list->tail->content);
		token = token_handler(TH_PEEK, NULL);
	}
	token_handler(TH_END, NULL);
	if (!check_token_type(token->type, TT_EMPTY))
	{
		set_question(g_env_list, PARSE_ERROR_STATUS);
		minishell_errormsg("parse error", __FUNCTION__, NULL);
		parser_error(pipeline_list, token);
		delete_word_content(token);
		return (NULL);
	}
	delete_word_content(token);
	return (pipeline_list);
}

void	parse_pipeline(t_pipeline *pipeline)
{
	t_token		*token;
	t_dlist		*command_list;

	pipeline->command_list = dlist_init();
	command_list = pipeline->command_list;
	push_back(command_list, ft_calloc(1, sizeof(t_command)));
	parse_command(command_list->head->content);
	token = token_handler(TH_PEEK, NULL);
	while (check_token_type(token->type, TT_PIPE))
	{
		delete_word_content(token_handler(TH_GET, NULL));
		push_back(pipeline->command_list, ft_calloc(1, sizeof(t_command)));
		parse_command(command_list->tail->content);
		token = token_handler(TH_PEEK, NULL);
	}
}
