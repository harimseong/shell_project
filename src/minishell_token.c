/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:51:07 by hseong            #+#    #+#             */
/*   Updated: 2022/05/11 18:53:07 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "dlinkedlist.h"
#include "minishell_token.h"
#include <readline/readline.h>
#include <stdlib.h>

t_dlist	*minishell_parse_token(char *cmdline)
{
	t_dlist			*token_list;
	t_token_context token_context;

	if (cmdline == NULL)
		return (NULL);
	token_context = (t_token_context){0, cmdline};
	token_list = dlist_init();
	while (*token_context.token_start)
	{
		
	}
	free(cmdline);
	return (token_list);
}

void	minishell_analyze_token(t_dlist *token_list)
{
	if (token_list == NULL)
		return (NULL);
}
