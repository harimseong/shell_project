/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_initialize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 21:31:07 by hseong            #+#    #+#             */
/*   Updated: 2022/06/15 09:58:17 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "readline/readline.h"
#include "readline/history.h"
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

#include "minishell.h"
#include "cmd.h"
#include "constants.h"

static int	set_prompt(char **prompt);
static int	find_option(const char *name);
static int	find_arg(const char *name);

static const char	*g_default_prompt = " $> ";

int	minishell_initialize(int argc, char **argv, char **prompt)
{
	int		idx;
	int		found_option;
	int		found_arg;

	handle_signals();
	dup2(STDIN_FILENO, 10);
	dup2(STDOUT_FILENO, 11);
	rl_catch_signals = 0;
	if (argc == 1)
		return (set_prompt(prompt));
	idx = 0;
	while (argv[idx] != NULL)
	{
		found_option = find_option(argv[idx]);
		found_arg = find_arg(argv[idx]);
		if (found_option == FALSE && found_arg == FALSE)
		{
			if (found_option == FALSE)
				minishell_errormsg(argv[idx], "invaild option", NULL);
			else
				minishell_errormsg(NULL, NULL, NULL);
			return (1);
		}
		++idx;
	}
	return (0);
}

int	find_option(const char *name)
{
	int		comp_len;

	comp_len = ft_strlen(name);
	if (comp_len < 2)
		comp_len = 2;
	if (ft_strncmp(name, "-c", comp_len) == 0)
		return (TRUE);
	else if (name[0] == '-')
		return (FALSE);
	return (TRUE);
}

int	find_arg(const char *name)
{
	(void)name;
	return (0);
}

int	set_prompt(char **prompt)
{
	char	*front;

	front = getenv("USER");
	*prompt = ft_strjoin(front, g_default_prompt);
	return (*prompt == NULL);
}
