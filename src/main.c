/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:00:17 by hseong            #+#    #+#             */
/*   Updated: 2022/05/26 20:41:27 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <unistd.h>

#include "dlinkedlist.h"
#include "libft.h"
#include "minishell.h"
#include "../cmd_temp/cmd.h"

static const char	*g_prompt = "$> ";

int	main(int argc, char *argv[], char *envp[])
{
	t_dlist		*pipeline_list;
	t_dlist		*env_list;

	pipeline_list = (void *)1;
	env_list = dlist_init();
	env_list = set_envlist(envp, env_list);
	(void)argc;
	(void)argv;
	(void)envp;
	while (pipeline_list != NULL)
	{
		pipeline_list = temp_parse(readline(g_prompt), env_list);
		//parse(readline(g_prompt));
		//delete_dlist(token_list, delete_item);
	}
	return (0);
}

/*
void	print_item(t_token *token)
{
	ft_putstr_fd(token->token, 1);
	write(1, " ", 1);
}
*/
