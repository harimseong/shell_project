/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:00:17 by hseong            #+#    #+#             */
/*   Updated: 2022/06/06 15:59:21 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <unistd.h>

#include "dlinkedlist.h"
#include "libft.h"
#include "minishell.h"
#include "../cmd_temp/cmd.h"
#include "parser/parser.h"

static void	get_argument(int argc, char **argv);

static const char	*g_prompt = "$> ";

int	main(int argc, char *argv[], char *envp[])
{
	t_dlist		*pipeline_list;
	t_dlist		*env_list;

	pipeline_list = (void *)1;
	env_list = dlist_init();
	env_list = set_envlist(envp, env_list);
	get_argument(argc, argv);
	while (1)
	{
		//pipeline_list = temp_parse(readline(g_prompt), env_list);
		pipeline_list = parser(readline(g_prompt), env_list);
		if (pipeline_list == NULL)
			continue ;
		dlist_print_forward(pipeline_list, pipeline_list_print);
		dlist_delete(pipeline_list, pipeline_list_delete);
	}
	return (0);
}

void	get_argument(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}
/*
void	print_item(t_token *token)
{
	ft_putstr_fd(token->token, 1);
	write(1, " ", 1);
}
*/
