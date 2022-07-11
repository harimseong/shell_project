/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:45:20 by hseong            #+#    #+#             */
/*   Updated: 2022/07/11 15:35:02 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#include "minishell.h"
#include "cmd.h"
#include "execute.h"
#include "parser/parser.h"

int			execute_command(t_dlist *word_list, t_dlist *env_list);
int			set_redirect(t_dlist *redirect_list);
static int	fork_and_pipe(int *recent_read_end,
				int *pipe_fd, int pipe_exist);
static int	safe_dup2(int oldfd, int newfd, int line);

int	generate_process(t_command *command, t_dlist *env_list, int pipe_exist)
{
	static int	recent_read_end;
	int			pid;
	int			status;
	int			pipe_fd[2];

	pid = fork_and_pipe(&recent_read_end, pipe_fd, pipe_exist);
	handle_signals_cmd_parent();
	if (pid == 0)
	{
		handle_signals_cmd_child();
		status = set_redirect(command->redirect_list);
		if (status == 0 && command->word_list->size > 0)
			execute_command(command->word_list, env_list);
		builtin_set_exit(env_list, status, 0, NULL);
	}
	minishell_assert(pid >= 0, __FILE__, __LINE__);
	return (pid);
}

static int	fork_and_pipe(int *recent_read_end, int *pipe_fd, int pipe_exist)
{
	int	pid;
	int	status;

	status = pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		if (*recent_read_end > 0)
			safe_dup2(*recent_read_end, STDIN_FILENO, __LINE__);
		if (pipe_exist)
			safe_dup2(pipe_fd[1], STDOUT_FILENO, __LINE__);
		else
			minishell_assert(close(pipe_fd[1]) >= 0, __FILE__, __LINE__);
		return (status < 0);
	}
	minishell_assert(close(pipe_fd[1]) >= 0, __FILE__, __LINE__);
	if (*recent_read_end != 0)
		minishell_assert(close(*recent_read_end) >= 0, __FILE__, __LINE__);
	*recent_read_end = pipe_fd[0] * pipe_exist;
	if (!pipe_exist)
		minishell_assert(close(pipe_fd[0]) >= 0, __FILE__, __LINE__);
	return (pid - (pid + 1) * (status < 0));
}

static int	safe_dup2(int oldfd, int newfd, int line)
{
	int	status;

	status = dup2(oldfd, newfd);
	minishell_assert(status >= 0 && close(oldfd) == 0, __FILE__, line);
	return (status);
}
