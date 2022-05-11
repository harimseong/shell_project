/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:51:07 by hseong            #+#    #+#             */
/*   Updated: 2022/05/11 15:44:52 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "dlinkedlist.h"
#include "minishell_token.h"
#include <readline/readline.h>
#include <stdlib.h>

t_dlist	*minishell_parse_token(char *cmd_line)
{
	t_dlist			*token_list;
	t_token_context token_context;

	token_context = (t_token_context){0, 0};
	if (cmd_line == NULL)
		return (NULL);
	token_list = dlist_init();

	free(cmd_line);
	return (token_list);
}
