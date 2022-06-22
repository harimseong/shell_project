/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 00:02:08 by gson              #+#    #+#             */
/*   Updated: 2022/06/22 19:50:51 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include "readline/readline.h"
#include "readline/history.h"

#include "minishell.h"
#include "cmd.h"

/*
 * forked child have duplicate signals from parent.
 * but execve sets those to differently.
 * ignored signals are kept ignored,
 * handled signals are set to default.
 *
 */

/*
 * SIGINT handler for child process before execve
 */
static void	handle_sigint_cmd(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

/*
 * SIGINT handler for shell while child processes are running
 * Ctrl-C sets the status to 1.
 * global variable is necessary here to access the status.
 */
static void	handle_sigint(int signo)
{
	status_handler(1, NULL, SH_SET);
	if (signo == SIGINT)
	{
		rl_catch_signals = 0;
		printf("\n");
		if (DEBUG_FLAG)
			printf("%-4.d|", status_handler(0, NULL, SH_GET));
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_signals_cmd_parent(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint_cmd);
}

void	handle_signals_cmd_child(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, handle_sigint_cmd);
}

void	handle_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
}
