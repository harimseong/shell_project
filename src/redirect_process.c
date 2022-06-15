/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 20:48:13 by hseong            #+#    #+#             */
/*   Updated: 2022/06/15 18:47:06 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "readline/readline.h"
#include "readline/history.h"
#include "libft.h"

#include "execute.h"
#include "parser/parser.h"

char		*get_next_line(int fd);
//static char	*get_next_line_prompt(int fd, const char *prompt);

static const char	*g_heredoc_prompt = "> ";

int	redirect_in(t_redirect *redirect)
{
	int		fd;

	fd = open(redirect->filename, O_RDONLY);
	if (fd < 0 || dup2(fd, STDIN_FILENO) < 0)
		return (1);
	redirect->descriptor = fd;
	redirect->redir_type = REDIR_PROCESSED;
	return (0);
}

int	redirect_out(t_redirect *redirect)
{
	int		fd;

	fd = open(redirect->filename, O_RDWR | O_CREAT | O_TRUNC, 0664);
	// O_NOCTTY?
	if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0)
		return (1);
	redirect->descriptor = fd;
	redirect->redir_type = REDIR_PROCESSED;
	return (0);
}

int	redirect_append(t_redirect *redirect)
{
	int		fd;

	fd = open(redirect->filename, O_RDWR | O_CREAT | O_APPEND, 0664);
	if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0)
		return (1);
	redirect->descriptor = fd;
	redirect->redir_type = REDIR_PROCESSED;
	return (0);
}

// readline history should be considered
int	redirect_heredoc(t_redirect *redirect)
{
	char	*string;
	char	*heredoc;
	int		pipe_fd[2];
	int		temp_out;
	int		temp_in;

	if (pipe(pipe_fd) < 0)
		return (1);
	heredoc = redirect->heredoc;
	temp_in = dup(STDIN_FILENO);
	temp_out = dup(STDOUT_FILENO);
	dup2(MINISHELL_STDIN, STDIN_FILENO);
	dup2(MINISHELL_STDOUT, STDOUT_FILENO);
	string = readline(g_heredoc_prompt);
	while (string && ft_strncmp(string, heredoc,
			ft_strlen(heredoc) + 1) != 0)
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
	dup2(temp_in, STDIN_FILENO);
	dup2(pipe_fd[0], STDIN_FILENO);
	redirect->descriptor = STDIN_FILENO;
	redirect->redir_type = REDIR_PROCESSED;
	return (0);
}

/*
char	*get_next_line_prompt(int fd, const char *prompt)
{
	ft_putstr_fd(prompt, STDERR_FILENO);
	return (get_next_line(fd));
}
*/
