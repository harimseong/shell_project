/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:00:17 by hseong            #+#    #+#             */
/*   Updated: 2022/06/09 23:18:35 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

#include "dlinkedlist.h"
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

	pipeline_list = (void *)1;
	env_list = dlist_init();
	env_list = set_envlist(envp, env_list);
	prompt = minishell_initialize(argc, argv);
	export(env_list, 1, NULL);
	while (1)
	{
		line = readline(prompt);
		if (line == NULL)
			break ;
		pipeline_list = parser(line, env_list);
		if (pipeline_list == NULL)
			continue ;
		process_pipeline(pipeline_list, env_list);
		dlist_print_forward(pipeline_list, pipeline_content_print);
		dlist_delete(pipeline_list, delete_pipeline_content);
	}
	return (0);
}
