/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:22:49 by hseong            #+#    #+#             */
/*   Updated: 2022/06/08 04:39:04 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/errno.h>
#include <unistd.h>

#include "dlinkedlist.h"
#include "libft.h"
#include "../cmd_temp/cmd.h"
#include "types.h"
#include "constants.h"
#include "errors.h"
#include "parser/token.h"
#include "parser/parser.h"
#include "parser/token_recognition.h"
#include "minishell.h"

void			parse_command(t_command *command);
static void		parse_pipeline(t_pipeline *pipeline);
static t_dlist	*parse_init(t_dlist *pipeline_list);

/*
t_dlist *temp_parse(const char *line, t_dlist *env_list)
{
	char		**temp;
	int			temp_len;

	if (line == NULL)
		return (NULL);
	temp_len = 0;
	temp = ft_split(line, " ");
	while (temp[temp_len])
		++temp_len;
	if (temp_len == 0)
		return ((void *)1);
	if (ft_strcmp(temp[0], "export") == 0)
		builtin_export(env_list, temp_len, temp);
	else if (ft_strcmp(temp[0], "env") == 0)
		builtin_env(env_list);
	return ((void *)1);
}
*/

t_dlist	*parser(const char *line, t_dlist *env_list)
{
	t_dlist		*dlist_line;
	t_token		*token;
	t_iterator	iterator;
	char		*arr_line;

	if (line == NULL)
		return (NULL);
	dlist_line = dlist_init_arr(line, sizeof(char), ft_strlen(line) + 1);
	iterator = (t_iterator){NULL, dlist_line, 0, env_list};
	if (DEBUG_FLAG)
	{
		arr_line = convert_list(dlist_line->head, dlist_line->size);
		printf("debug: input line: %s\n", arr_line);
		free(arr_line);
	}
	token_handler(TH_SET, &iterator);
	token = token_handler(TH_PEEK, NULL);
	if (token->type == TT_EMPTY)
		return (NULL);
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
	if (token->type != TT_EMPTY)
	{
		if (DEBUG_FLAG)
			printf("minishell: parse error: %s: %s: %d: token_type %x\n",
				__FILE__, __FUNCTION__, __LINE__, token->type);
		parser_error(pipeline_list, token);
		return (NULL);
	}
	return (pipeline_list);
}

/*
t_dlist	*parse(const char *line)
{
	t_iterator	iterator;
	t_dlist		*pipeline_list;
	t_token		*token;

	iterator = (t_iterator){(char *)line, 0, 0};
	token_handler(TH_SET, &iterator);
	token = token_handler(TH_PEEK, NULL);
	if (token->type == 0)
		return (NULL);
	pipeline_list = dlist_init();
	push_back(pipeline_list, ft_calloc(1, sizeof(t_pipeline)));
	parse_pipeline(pipeline_list->head->content);
	token = token_handler(TH_PEEK, NULL);
	while (check_token_type(token->type, TRUE))
	{
		push_back(pipeline_list, ft_calloc(1, sizeof(t_pipeline)));
		parse_pipeline(pipeline_list->tail->content);
		token = token_handler(TH_PEEK, NULL);
	}
	if (token->type != TT_EMPTY)
	{
		parser_error(pipeline_list, token);
		return (NULL);
	}
	return (pipeline_list);
}
*/

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
