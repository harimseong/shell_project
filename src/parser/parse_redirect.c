/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 21:50:29 by hseong            #+#    #+#             */
/*   Updated: 2022/05/26 21:55:36 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlinkedlist.h"
#include "libft.h"
#include "parser/token.h"
#include "parser/parser.h"

static void	parse_io_file(t_iterator *iterator, t_dlist *pipeline_list);
static void	parse_io_heredoc(t_iterator *iterator, t_dlist *pipeline_list);

void	parse_io_redirect(t_iterator *iterator, t_dlist *pipeline_list)
{
	t_token		*token;
	size_t		len;

	token = token_handler(iterator, TOKEN_PEEK);
	len = ft_strlen(token->word);
	if (token->type == DLESS)
		parse_io_heredoc(iterator, pipeline_list);
	else if (token->type == '<' || token->type == '>'
		|| token->type == DGREAT)
		parse_io_file(iterator, pipeline_list);
	else
		parser_error(token);
}

void	parse_io_file(t_iterator *iterator, t_dlist *pipeline_list)
{
	(void)iterator;
	(void)pipeline_list;
}

void	parse_io_heredoc(t_iterator *iterator, t_dlist *pipeline_list)
{
	(void)iterator;
	(void)pipeline_list;
}
