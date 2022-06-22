/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:00:17 by hseong            #+#    #+#             */
/*   Updated: 2022/06/22 19:51:15 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "readline/readline.h"
#include "readline/history.h"
#include "libft.h"

#include "minishell.h"
#include "cmd.h"
#include "parser/parser.h"

int			minishell_initialize(int argc, char **argv, t_dlist *env_list,
				char **prompt);
static void	prompt_info(void);

int	main(int argc, char *argv[], char *envp[])
{
	t_dlist			*pipeline_list;
	t_dlist			*env_list;
	char			*line;
	char			*prompt;

	env_list = set_envlist(envp, dlist_init());
	status_handler(0, env_list, SH_START);
	if (minishell_initialize(argc, argv, env_list, &prompt))
		builtin_exit(env_list, 0, NULL);
	while (prompt)
	{
		prompt_info();
		line = readline(prompt);
		if (line == NULL)
			builtin_print_exit(env_list, 0, NULL);
		if (ft_strlen(line) > 0)
			add_history(line);
		pipeline_list = parser(line, env_list);
		free(line);
		if (pipeline_list == NULL)
			continue ;
		read_pipeline(pipeline_list, env_list);
		dlist_delete(pipeline_list, delete_pipeline_content);
	}
	return (1);
}
//				inspection tools
// opened fd:
// 		system("lsof -p $$");
// token list:
// 		dlist_print_forward(pipeline_list, pipeline_content_print);
// leak check:
// 		system("leaks minishell");

void	prompt_info(void)
{
	if (DEBUG_FLAG)
		printf("%-4.d|", status_handler(0, NULL, SH_GET));
}

char	**get_argv(char **new_argv)
{
	static char		**argv;

	if (new_argv != NULL)
		argv = new_argv;
	return (argv);
}
