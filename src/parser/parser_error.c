/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 21:26:37 by hseong            #+#    #+#             */
/*   Updated: 2022/07/07 21:31:30 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

#include "minishell.h"
#include "parser/parser.h"

void	parser_error(t_dlist *pipeline_list, t_token *token)
{
	char	*temp_str;

	dlist_delete(pipeline_list, delete_pipeline_content);
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
