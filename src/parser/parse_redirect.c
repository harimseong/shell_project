/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 21:50:29 by hseong            #+#    #+#             */
/*   Updated: 2022/05/27 21:14:45 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlinkedlist.h"
#include "libft.h"
#include "constants.h"
#include "parser/token.h"
#include "parser/parser.h"

static void	parse_io_file(t_dlist *redirect_list);
static void	parse_io_heredoc(t_dlist *redirect_list);

void	parse_io_redirect(t_dlist *redirect_list)
{
	t_token		*token;

	token = token_handler(TH_PEEK, NULL);
	if (token->type == TT_DLESS)
		parse_io_heredoc(redirect_list);
	else if ((token->type & TT_REDIRECT) == TRUE)
		parse_io_file(redirect_list);
}

void	parse_io_file(t_dlist *redirect_list)
{
	t_token		*operator;
	t_token		*filename;

	operator = token_handler(TH_GET, NULL);
	push_back(redirect_list, operator);
	filename = token_handler(TH_PEEK, NULL);
	if (filename->type != TT_WORD)
	{
		filename->type = TT_ERROR;
		return ;
	}
	filename = token_handler(TH_GET, NULL);
	push_back(redirect_list, filename);
}

void	parse_io_heredoc(t_dlist *redirect_list)
{
	t_token		*heredoc;
	t_token		*end_word;

	heredoc = token_handler(TH_GET, NULL);
	push_back(redirect_list, heredoc);
	end_word = token_handler(TH_PEEK, NULL);
	if (end_word->type != TT_WORD)
	{
		end_word->type = TT_ERROR;
		return ;
	}
	end_word = token_handler(TH_GET, NULL);
	push_back(redirect_list, end_word);
}
