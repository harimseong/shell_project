/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 00:02:08 by gson              #+#    #+#             */
/*   Updated: 2022/06/14 23:33:45 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include "readline/readline.h"
#include "readline/history.h"
#include "cmd.h"
#include "minishell.h"

extern t_dlist	*g_env_list;

static void	handle_sigint_child(int signo)
{
	set_question(g_env_list, 130);
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

static void	handle_sigint(int signo)
{
	set_question(g_env_list, 1);
	if (signo == SIGINT)
	{
		rl_catch_signals = 0;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_signals_cmd(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint_child);
}

void	handle_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
}
