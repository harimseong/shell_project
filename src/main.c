/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:00:17 by hseong            #+#    #+#             */
/*   Updated: 2022/06/13 01:13:16 by gson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "libft.h"

#include "minishell.h"
#include "cmd.h"
#include "parser/parser.h"

char		*minishell_initialize(int argc, char **argv);

int	main(int argc, char *argv[], char *envp[])
{
	t_dlist		*pipeline_list;
	t_dlist		*env_list;
	char		*line;
	char		*prompt;

	handle_signals();
	pipeline_list = (void *)1;
	env_list = set_envlist(envp, dlist_init());
	prompt = minishell_initialize(argc, argv);
	while (1)
	{
		line = readline(prompt);
		if (line == NULL)
			break ;
		pipeline_list = parser(line, env_list);
		if (pipeline_list == NULL)
			continue ;
//		dlist_print_forward(pipeline_list, pipeline_content_print);
		read_pipeline(pipeline_list, env_list);
		dlist_delete(pipeline_list, delete_pipeline_content);
//		system("leaks minishell");
	}
// 	free env_list in Ctrl-D signal handler
	return (0);
}
