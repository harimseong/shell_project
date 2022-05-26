/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:22:49 by hseong            #+#    #+#             */
/*   Updated: 2022/05/26 22:03:30 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "../cmd_temp/cmd.h"
#include "dlinkedlist.h"
#include "types.h"
#include "parser/token.h"
#include "parser/parser.h"

static void	parse_pipeline(t_iterator *iterator, t_dlist *pipeline_list);
void	parse_command(t_iterator *iterator, t_dlist *pipeline_list);

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

t_dlist	*parse(const char *line)
{
	t_iterator	iterator;
	t_dlist		*pipeline_list;
	t_token		*token;

	pipeline_list = dlist_init();
	push_back(pipeline_list, malloc(sizeof(t_pipeline)));
	iterator = (t_iterator){(char *)line, 0};
	parse_pipeline(&iterator, pipeline_list);
	token = token_handler(&iterator, TOKEN_PEEK);
	while (ft_strcmp(token->word, "&&") == 0
			|| ft_strcmp(token->word, "||"))
	{
		parse_pipeline(&iterator, pipeline_list);
		token = token_handler(&iterator, TOKEN_PEEK);
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
	token = token_handler(iterator, TOKEN_PEEK);
	while (token->type == '|')
	{
		parse_command(iterator, pipeline_list);
		token = token_handler(iterator, TOKEN_PEEK);
	}
}

void	parser_error(t_token *token)
{
	(void)token;
}

t_token	*token_handler(t_iterator *iterator, int type)
{
	(void)iterator;
	(void)type;
	return (NULL);
}
