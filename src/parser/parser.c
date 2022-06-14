/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:22:49 by hseong            #+#    #+#             */
/*   Updated: 2022/06/14 23:44:41 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "readline/readline.h"
#include "readline/history.h"
#include <stdlib.h>
#include <sys/errno.h>
#include <unistd.h>
#include "libft.h"

#include "minishell.h"
#include "cmd.h"
#include "parser/token.h"
#include "types.h"
#include "constants.h"
#include "errors.h"
#include "parser/parser.h"
#include "parser/token_recognition.h"

#define PARSE_ERROR_STATUS (258)

extern t_dlist	*g_env_list;

void			parse_command(t_command *command);
static void		parse_pipeline(t_pipeline *pipeline);
static t_dlist	*parse_init(t_dlist *pipeline_list);

t_dlist	*parser(const char *line, t_dlist *env_list)
{
	t_dlist		*dlist_line;
	t_token		*token;
	t_iterator	iterator;
	char		*arr_line;

	if (line == NULL)
		return (NULL);
	dlist_line = array_to_dlist_init(line, sizeof(char), ft_strlen(line) + 1);
	iterator = (t_iterator){NULL, dlist_line, 0, env_list};
	if (0)//DEBUG_FLAG)
	{
		arr_line = dlist_to_string(dlist_line->head, dlist_line->size);
		printf("debug: input line: %s\n", arr_line);
		free(arr_line);
	}
	token_handler(TH_SET, &iterator);
	token = token_handler(TH_PEEK, NULL);
	if (check_token_type(token->type, TT_EMPTY))
	{
		delete_word_content(token);
		token_handler(TH_END, NULL);
		return (NULL);
	}
	add_history(line);
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
		token_handler(TH_GET, NULL);
		push_back(pipeline_list, ft_calloc(1, sizeof(t_pipeline)));
		parse_pipeline(pipeline_list->tail->content);
		token = token_handler(TH_PEEK, NULL);
	}
	token_handler(TH_END, NULL);
	if (!check_token_type(token->type, TT_EMPTY))
	{
		set_question(g_env_list, PARSE_ERROR_STATUS);
		if (DEBUG_FLAG)
			printf("minishell: parse error: %s: %s: %d: token_type %x\n",
				__FILE__, __FUNCTION__, __LINE__, token->type);
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
		token_handler(TH_GET, NULL);
		push_back(pipeline->command_list, ft_calloc(1, sizeof(t_command)));
		parse_command(command_list->tail->content);
		token = token_handler(TH_PEEK, NULL);
	}
}
