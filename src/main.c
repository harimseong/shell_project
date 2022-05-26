/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:00:17 by hseong            #+#    #+#             */
/*   Updated: 2022/05/26 20:20:07 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <unistd.h>

#include "../cmd_temp/cmd.h"
#include "dlinkedlist.h"
#include "minishell.h"
#include "libft.h"

t_dlist	*envlist;

static const char	*g_prompt = "$> ";
t_dlist *temp_parse(const char *line);

int	main(int argc, char *argv[], char *envp[])
{
	t_dlist		*pipeline_list;

	pipeline_list = (void *)1;
	envlist = dlist_init();
	envlist = set_envlist(envp, envlist);
	(void)argc;
	(void)argv;
	(void)envp;
	while (pipeline_list != NULL)
	{
		pipeline_list = temp_parse(readline(g_prompt));
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
