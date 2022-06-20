/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_wrapper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:15:41 by hseong            #+#    #+#             */
/*   Updated: 2022/06/20 21:57:19 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include <sys/stat.h>

#include <unistd.h>
#include <string.h>
#include "libft.h"

#include "minishell.h"
#include "constants.h"
#include "execute.h"

static int	get_execute_status(int errno_var);
static int	print_error_execve(int errno_var, const char *filename);

enum e_execve_status
{
	ES_PERM = 126,
	ES_EACCES = 126,
	ES_ENOENT = 127
	
};

static const int	g_status_tab[128]
	= {
	0, ES_PERM, ES_ENOENT, 0, 0, 0, 0, 0,
	0, 0, 0, 0, ES_EACCES, 0, 0, 0,/* 15*/
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,/* 31*/
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,/* 47*/
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,/* 63*/
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,/* 79*/
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,/* 95*/
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,/*111*/
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,/*127*/
};

// access to directory leads to Permission denied error (EACCES)
// check the name whether directory or not with stat().
int	execve_wrapper(const char *filename, char **argv, char **envp,
	char **path_arr)
{
	char	*file_path;

	minishell_assert(ft_strlen(filename) < MAX_PATHNAME, __FILE__, __LINE__);
	file_path = ft_strrchr(filename, '/');
	if (file_path == NULL)
	{
		ft_execvpe(filename, argv, envp, path_arr);
		minishell_errormsg(filename, "command not found", NULL);
		return (ES_ENOENT);
	}
	else
		execve(filename, argv, envp);
	minishell_assert(print_error_execve(errno, filename), __FILE__, __LINE__);
	return (get_execute_status(errno));
}

int	get_execute_status(int errno_var)
{
	if (g_status_tab[errno_var] != 0)
		return (g_status_tab[errno_var]);
	return (errno_var);
}

int	print_error_execve(int errno_var, const char *filename)
{
	struct stat	status_info;

	if (stat(filename, &status_info) != 0)
		return (0);
	if (errno_var == ENOENT)
	minishell_errormsg(filename, "command not found", NULL);
	else if (errno_var == EACCES)
	{
		if (status_info.st_mode == S_IFDIR)
			minishell_errormsg(filename, "is a directory", NULL);
		else
			minishell_errormsg(filename, strerror(errno), NULL);
	}
	else
		minishell_errormsg(filename, strerror(errno), NULL);
	return (1);
}

/*
static int	print_error_execvpe(int errno_var, const char *filename);

int	print_error_execvpe(int errno_var, const char *filename)
{
	struct stat	status_info;

	if (stat(filename, &status_info) != 0)
		return (0);
	if (errno_var == ENOENT)
	minishell_errormsg(filename, "command not found", NULL);
	else if (errno_var == EACCES)
	{
		if (status_info.st_mode == S_IFDIR)
			minishell_errormsg(filename, "is a directory", NULL);
		else if (status_info.st_mode == S_IFREG)
			minishell_errormsg(filename, "is a directory", NULL);
		else
			minishell_errormsg(filename, strerror(errno), NULL);
	}
	else
		minishell_errormsg(filename, strerror(errno), NULL);
	return (1);
}
*/
