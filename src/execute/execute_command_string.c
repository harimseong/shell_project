/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_string.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 22:16:58 by hseong            #+#    #+#             */
/*   Updated: 2022/06/19 19:45:02 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlinkedlist.h"
#include <stdio.h>

#include "minishell.h"
#include "parser/parser.h"

static int	set_arg(int argc, char **argv);

// argc    0  1                2    3    4
// minishell -c "command string" arg1 arg2 ...
int	execute_command_string(int argc, char **argv, t_dlist *env_list)
{
	t_dlist		*pipeline_list;
	char		*line;

	minishell_assert(set_arg(argc - 3, argv + 3) == 0, __FILE__, __LINE__);
	line = argv[2];
	if (line == NULL)
	{
		minishell_errormsg(argv[1], "option requires an argument", NULL);
		builtin_set_exit(env_list, 2, 0, NULL);
	}
	pipeline_list = parser(line, env_list);
	if (pipeline_list == NULL)
		return (1);
	if (DEBUG_FLAG)
		dlist_print_forward(pipeline_list, pipeline_content_print);
	read_pipeline(pipeline_list, env_list);
	dlist_delete(pipeline_list, delete_pipeline_content);
	builtin_exit(env_list, 0, NULL);
	return (0);
}
//	dlist_print_forward(pipeline_list, pipeline_content_print);

int	set_arg(int argc, char **argv)
{
	int		idx;

	(void)argv;
	if (argc > 9)
		return (1);
	idx = 0;
	while (idx < argc)
		++idx;
	return (0);
}
