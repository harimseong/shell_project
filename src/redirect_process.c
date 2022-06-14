/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 20:48:13 by hseong            #+#    #+#             */
/*   Updated: 2022/06/14 22:16:29 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

#include "execute.h"
#include "parser/parser.h"

static const char	*g_heredoc_prompt = "> ";

int	redirect_in(t_redirect *redirect, int std_fd_set[2])
{
	int		fd;

	(void)std_fd_set;
	fd = open(redirect->filename, O_RDONLY);
	if (fd < 0 || dup2(fd, STDIN_FILENO) < 0)
		return (1);
	redirect->descriptor = fd;
	redirect->redir_type = REDIR_PROCESSED;
	return (0);
}

int	redirect_out(t_redirect *redirect, int std_fd_set[2])
{
	int		fd;

	(void)std_fd_set;
	fd = open(redirect->filename, O_RDWR | O_CREAT | O_TRUNC, 0664);
	// O_NOCTTY?
	if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0)
		return (1);
	redirect->descriptor = fd;
	redirect->redir_type = REDIR_PROCESSED;
	return (0);
}

int	redirect_append(t_redirect *redirect, int std_fd_set[2])
{
	int		fd;

	(void)std_fd_set;
	fd = open(redirect->filename, O_RDWR | O_CREAT | O_APPEND, 0664);
	if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0)
		return (1);
	redirect->descriptor = fd;
	redirect->redir_type = REDIR_PROCESSED;
	return (0);
}

// readline history should be considered
int	redirect_heredoc(t_redirect *redirect, int std_fd_set[2])
{
	char	*string;
	char	*heredoc;
	size_t	heredoc_len;
	int		pipe_fd[2];
	int		temp_out;

	if (pipe(pipe_fd) < 0)
		return (1);
	heredoc = redirect->heredoc;
	temp_out = dup(STDOUT_FILENO);
	dup2(std_fd_set[1], STDOUT_FILENO);
	string = readline(g_heredoc_prompt);
	// Ctrl-D in heredoc
	heredoc_len = ft_strlen(heredoc);
	while (string && ft_strncmp(string, heredoc,
		ft_max(ft_strlen(string), heredoc_len)) != 0)
	{
		write(pipe_fd[1], string, ft_strlen(string));
		write(pipe_fd[1], "\n", 1);
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
