/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 20:48:13 by hseong            #+#    #+#             */
/*   Updated: 2022/06/11 23:09:16 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "libft.h"

#include "execute.h"
#include "parser/parser.h"

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

int	redirect_heredoc(t_redirect *redirect)
{
	char	*string;
	char	*heredoc;
	size_t	heredoc_len;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		return (1);
	heredoc = redirect->heredoc;
	heredoc_len = ft_strlen(heredoc);
	string = readline(g_heredoc_prompt);
	while (ft_strncmp(string, heredoc, heredoc_len) != 0)
	{
		write(pipe_fd[1], string, ft_strlen(string));
		free(string);
		string = readline(g_heredoc_prompt);
	}
	free(string);
	close(pipe_fd[1]);
	redirect->descriptor = pipe_fd[0];
	redirect->redir_type = REDIR_PROCESSED;
	return (0);
}
