/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:51:07 by hseong            #+#    #+#             */
/*   Updated: 2022/05/26 20:05:18 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "dlinkedlist.h"
#include "parser/token.h"
#include <readline/readline.h>
#include <stdlib.h>

int	minishell_parse_token(char *cmd_line)
{
	t_dlist			*token_list;
	t_token_context token_context;

	if (cmd_line == NULL)
		return (0);
	token_context = (t_token_context){cmd_line, 0, cmd_line, NULL};
	token_list = dlist_init();
	while (*token_context.token_itr)
		g_token_char_tab[(int)*token_context.cmd_line](token_list,
			&token_context);
	free(cmd_line);
	return (0);
}
