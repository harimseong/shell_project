/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_initialize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 21:31:07 by hseong            #+#    #+#             */
/*   Updated: 2022/06/16 19:15:08 by hseong           ###   ########.fr       */
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

static int	set_prompt(char **prompt);

static const char	*g_default_prompt = " $> ";

int	minishell_initialize(int argc, char **argv, char **prompt)
{
	(void)argc;
	(void)argv;
	(void)argc;
	handle_signals();
	dup2(STDIN_FILENO, MINISHELL_STDIN);
	dup2(STDOUT_FILENO, MINISHELL_STDOUT);
	rl_catch_signals = 0;
	set_prompt(prompt);
	return (0);
}

int	set_prompt(char **prompt)
{
	char	*front;

	front = getenv("USER");
	*prompt = ft_strjoin(front, g_default_prompt);
	return (*prompt == NULL);
}
