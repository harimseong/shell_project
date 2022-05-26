/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:22:49 by hseong            #+#    #+#             */
/*   Updated: 2022/05/26 20:20:02 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "../cmd_temp/cmd.h"
#include "dlinkedlist.h"
#include "types.h"
#include "parser/token.h"
//#include "parser/parser.h"

//static void	parse_pipeline(t_iterator *iterator, t_dlist *pipeline_list);
void	parse_command(t_iterator *iterator, t_dlist *pipeline_list);

extern t_dlist	*envlist;

t_dlist *temp_parse(const char *line)
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
		builtin_export(envlist, temp_len, temp);
	else if (ft_strcmp(temp[0], "env") == 0)
		builtin_env(envlist);
	return ((void *)1);
}

/*
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

*/
