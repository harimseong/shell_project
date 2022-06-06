/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 21:50:29 by hseong            #+#    #+#             */
/*   Updated: 2022/06/06 20:04:45 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

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
	else if ((token->type & TT_REDIRECT) == TT_REDIRECT)
		parse_io_file(redirect_list);
}

void	parse_io_file(t_dlist *redirect_list)
{
	t_token			*operator;
	t_token			*filename;
	t_redirect		*redirect;
	enum e_redir	type;

	operator = token_handler(TH_GET, NULL);
	filename = token_handler(TH_PEEK, NULL);
	if (filename->type != TT_WORD)
	{
		if (DEBUG_FLAG)
			printf("minishell: parse error: %s: %s: %d: token_type %x\n",
				__FILE__, __FUNCTION__, __LINE__, filename->type);
		filename->type = TT_ERROR;
		return ;
	}
	filename = token_handler(TH_GET, NULL);
	redirect = malloc(sizeof(t_redirect));
	type = (operator->type == TT_LESS) * REDIR_IN
		+ (operator->type == TT_GREAT) * REDIR_OUT
		+ (operator->type == TT_DGREAT) * REDIR_APPEND;
	*redirect = (t_redirect){type, -1, NULL,
		{operator, filename}};
	push_back(redirect_list, redirect);
}

void	parse_io_heredoc(t_dlist *redirect_list)
{
	t_token		*heredoc;
	t_token		*end_word;
	t_redirect	*redirect;

	heredoc = token_handler(TH_GET, NULL);
	end_word = token_handler(TH_PEEK, NULL);
	if (end_word->type != TT_WORD)
	{
		if (DEBUG_FLAG)
			printf("minishell: parse error: %s: %s: %d: token_type %x\n",
				__FILE__, __FUNCTION__, __LINE__, end_word->type);
		end_word->type = TT_ERROR;
		return ;
	}
	end_word = token_handler(TH_GET, NULL);
	redirect = malloc(sizeof(t_redirect));
	*redirect = (t_redirect){REDIR_HEREDOC, -1, end_word->word,
		{heredoc, end_word}};
	push_back(redirect_list, redirect);
}
