/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 21:26:37 by hseong            #+#    #+#             */
/*   Updated: 2022/06/16 19:15:52 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

#include "minishell.h"
#include "parser/parser.h"

void	parser_error(t_dlist *pipeline_list, t_token *token)
{
	dlist_delete(pipeline_list, delete_pipeline_content);
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	if (token->word == NULL)
		ft_putstr_fd("newline", STDERR_FILENO);
	else
		ft_putstr_fd(token->word, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}
