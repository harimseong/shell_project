/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 21:26:37 by hseong            #+#    #+#             */
/*   Updated: 2022/07/08 17:29:56 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <unistd.h>
#include "libft.h"

#include "minishell.h"
#include "parser/parser.h"

static void	parser_eof_error(t_token *token);

void	parser_error(t_dlist *pipeline_list, t_token *token)
{
	char	*temp_str;

	dlist_delete(pipeline_list, delete_pipeline_content);
	if (check_token_type(token->type, TT_EOF_ERROR))
	{
		parser_eof_error(token);
		return ;
	}
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	if (token->word == NULL)
		ft_putstr_fd("newline", STDERR_FILENO);
	else
		ft_putstr_fd(token->word, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	if (DEBUG_FLAG)
	{
		temp_str = ft_itoa(token->type);
		ft_putstr_fd("token type: ", STDERR_FILENO);
		ft_putendl_fd(temp_str, STDERR_FILENO);
		free(temp_str);
	}
}

static void	parser_eof_error(t_token *token)
{
	if (check_token_type(token->type, TT_SQUOTE_ERROR))
		minishell_errormsg("unexpected error while looking for matching `''", NULL, NULL);
	if (check_token_type(token->type, TT_DQUOTE_ERROR))
		minishell_errormsg("unexpected error while looking for matching `\"'", NULL, NULL);
	minishell_errormsg("syntax error:", "unexpected end of file", NULL);
}
