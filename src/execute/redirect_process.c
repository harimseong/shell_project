/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 20:48:13 by hseong            #+#    #+#             */
/*   Updated: 2022/06/22 19:08:45 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "readline/readline.h"
#include "readline/history.h"
#include "libft.h"

#include "execute.h"
#include "constants.h"
#include "parser/parser.h"

typedef int						(*t_redirect_func)(t_redirect *);

static const t_redirect_func	g_redirect_func_tab[REDIR_NUM_OPS] = {
	redirect_in,
	redirect_out,
	redirect_append,
	redirect_heredoc
};

static const char	*g_heredoc_prompt = "> ";

int	set_redirect(t_dlist *redirect_list)
{
	t_node		*node;
	t_redirect	*redirect;
	int			status;

	node = redirect_list->head;
	status = 0;
	while (status == 0 && node != NULL)
	{
		redirect = node->content;
		status = g_redirect_func_tab[redirect->redir_type](redirect);
		node = node->next;
	}
	return (status);
}

int	redirect_in(t_redirect *redirect)
{
	int		fd;

	fd = open(redirect->filename, O_RDONLY);
	if (fd < 0 || dup2(fd, STDIN_FILENO) < 0)
	{
		minishell_errormsg(redirect->filename, strerror(errno), NULL);
		return (1);
	}
	redirect->descriptor = fd;
	redirect->redir_type = REDIR_PROCESSED;
	return (0);
}

int	redirect_out(t_redirect *redirect)
{
	int		fd;

	fd = open(redirect->filename, O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0)
	{
		minishell_errormsg(redirect->filename, strerror(errno), NULL);
		return (1);
	}
	redirect->descriptor = fd;
	redirect->redir_type = REDIR_PROCESSED;
	return (0);
}

int	redirect_append(t_redirect *redirect)
{
	int		fd;

	fd = open(redirect->filename, O_RDWR | O_CREAT | O_APPEND, 0664);
	if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0)
	{
		minishell_errormsg(redirect->filename, strerror(errno), NULL);
		return (1);
	}
	redirect->descriptor = fd;
	redirect->redir_type = REDIR_PROCESSED;
	return (0);
}

// readline history should be considered
int	redirect_heredoc(t_redirect *redirect)
{
	char	*string;
	int		pipe_fd[2];
	int		temp_out;

	if (pipe(pipe_fd) < 0)
		return (minishell_assert(1, __FILE__, __LINE__));
	temp_out = dup(STDOUT_FILENO);
	dup2(MINISHELL_STDIN, STDIN_FILENO);
	dup2(MINISHELL_STDOUT, STDOUT_FILENO);
	string = readline(g_heredoc_prompt);
	while (string && ft_strncmp(string, redirect->heredoc,
			ft_strlen(redirect->heredoc) + 1) != 0)
	{
		ft_putendl_fd(string, pipe_fd[1]);
		free(string);
		string = readline(g_heredoc_prompt);
	}
	if (string != NULL)
		free(string);
	close(pipe_fd[1]);
	dup2(temp_out, STDOUT_FILENO);
	dup2(pipe_fd[0], STDIN_FILENO);
	redirect->descriptor = STDIN_FILENO;
	redirect->redir_type = REDIR_PROCESSED;
	return (0);
}
