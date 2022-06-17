/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:45:20 by hseong            #+#    #+#             */
/*   Updated: 2022/06/17 20:12:03 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/errno.h>
#include <signal.h>

#include "minishell.h"
#include "cmd.h"
#include "execute.h"
#include "parser/parser.h"

typedef int						(*t_redirect_func)(t_redirect *);

int			execute_command(t_dlist *word_list, t_dlist *env_list);
static int	set_redirect(t_dlist *redirect_list);
static int	fork_and_pipe(int *recent_read_end,
				int *pipe_fd, int pipe_exist);
static int	safe_dup2(int oldfd, int newfd, int line);

static const t_redirect_func	g_redirect_func_tab[REDIR_NUM_OPS] = {
	redirect_in,
	redirect_out,
	redirect_append,
	redirect_heredoc
};

int	generate_process(t_command *command, t_dlist *env_list, int pipe_exist)
{
	static int	recent_read_end;
	int			pid;
	int			status;
	int			pipe_fd[2];

	handle_signals_cmd();
	pid = fork_and_pipe(&recent_read_end, pipe_fd, pipe_exist);
	if (pid == 0)
	{
		status = set_redirect(command->redirect_list);
		minishell_assert(status == 0, __FILE__, __LINE__);
		if (status == 0 && command->word_list->size > 0)
			execute_command(command->word_list, env_list);
		builtin_set_exit(env_list, status, 0, NULL);
	}
	minishell_assert(pid >= 0, __FILE__, __LINE__);
	return (pid);
}

int	set_redirect(t_dlist *redirect_list)
{
	t_node		*node;
	t_redirect	*redirect;

	node = redirect_list->head;
	while (node != NULL)
	{
		redirect = node->content;
		g_redirect_func_tab[redirect->redir_type](redirect);
		node = node->next;
	}
	return (0);
}

int	fork_and_pipe(int *recent_read_end, int *pipe_fd, int pipe_exist)
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

int	safe_dup2(int oldfd, int newfd, int line)
{
	int	status;

	status = dup2(oldfd, newfd);
	minishell_assert(status >= 0 && close(oldfd) == 0, __FILE__, line);
	return (status);
}
