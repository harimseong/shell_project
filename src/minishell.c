/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:00:17 by hseong            #+#    #+#             */
/*   Updated: 2022/05/11 15:39:36 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "dlinkedlist.h"
#include <readline/readline.h>

static const char	*g_prompt = "$> ";

int	main(int argc, char *argv[], char *envp[])
{
	t_dlist		*token_list;

	token_list = (void *)1;
	while (token_list != NULL)
	{
		token_list = minishell_parse_token(readline(g_prompt));
		minishell_analyze_token(token_list);
		//delete_dlist(token_list, delete_item);
	}
	return (0);
}
