/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 21:31:07 by hseong            #+#    #+#             */
/*   Updated: 2022/06/22 19:47:40 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "readline/readline.h"
#include "readline/history.h"
#include "libft.h"

#include "minishell.h"
#include "cmd.h"
#include "constants.h"

#define OPTION_LIST_LEN (1)

static int	set_prompt(char **prompt);
static int	check_arg(int argc, char **argv, t_dlist *env_list);

int			execute_command_string(int argc, char **argv,
				t_dlist *env_list);
static const char	*g_default_prompt = " $> ";
static const char	*g_option_list[]
	= {
	"-c"
};

int	minishell_initialize(int argc, char **argv, t_dlist *env_list,
		char **prompt)
{
	get_argv(argv);
	minishell_assert(dup2(STDIN_FILENO, MINISHELL_STDIN)
		&& dup2(STDOUT_FILENO, MINISHELL_STDOUT), __FILE__, __LINE__);
	if (argc > 1)
		return (check_arg(argc, argv, env_list));
	handle_signals();
	rl_catch_signals = 0;
	set_prompt(prompt);
	return (0);
}

int	check_arg(int argc, char **argv, t_dlist *env_list)
{
	size_t	idx;

	idx = 0;
	while (idx < OPTION_LIST_LEN)
	{
		if (ft_strncmp(argv[1], g_option_list[idx],
				ft_strlen(g_option_list[idx]) + 1) == 0)
			break ;
		++idx;
	}
	if (idx == OPTION_LIST_LEN)
	{
		if (argv[1][0] == '-')
			minishell_errormsg("invalid option", NULL, NULL);
		else
			minishell_errormsg("arguments not supported", NULL, NULL);
		status_handler(2, NULL, SH_SET);
		return (1);
	}
	execute_command_string(argc, argv, env_list);
	return (1);
}

int	set_prompt(char **prompt)
{
	char	*front;

	front = getenv("USER");
	if (front == NULL)
	{
		*prompt = ft_strndup(g_default_prompt, ft_strlen(g_default_prompt));
		return (1);
	}
	*prompt = ft_strjoin(front, g_default_prompt);
	return (*prompt == NULL);
}
