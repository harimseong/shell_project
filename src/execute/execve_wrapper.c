/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_wrapper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:15:41 by hseong            #+#    #+#             */
/*   Updated: 2022/06/28 16:54:51 by hseong           ###   ########.fr       */
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
	0, 0, 0, 0, 0, ES_EACCES, 0, 0, /* 15*/
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, /* 31*/
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, /* 47*/
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, /* 63*/
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, /* 79*/
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, /* 95*/
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, /*111*/
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, /*127*/
};

// access to directory leads to Permission denied error (EACCES)
// check the name whether directory or not with stat().
int	execve_wrapper(const char *filename, char **argv, char **envp,
	char **path_arr)
{
	char	*file_path;
	int		errno_var;
	size_t	len;

	len = ft_strlen(filename);
	minishell_assert(len < MAX_PATHNAME, __FILE__, __LINE__);
	file_path = ft_strchr(filename, '/');
	if (file_path == NULL)
	{
		if (path_arr != NULL && path_arr[0] == NULL)
		{
			minishell_errormsg(filename, "No such file or directory", NULL);
			return (ES_ENOENT);
		}
		ft_execvpe(filename, argv, envp, path_arr);
		minishell_errormsg(filename, "command not found", NULL);
		return (ES_ENOENT);
	}
	else
		execve(filename, argv, envp);
	errno_var = errno;
	print_error_execve(errno_var, filename);
	return (get_execute_status(errno_var));
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
	mode_t		st_mode;

	if (stat(filename, &status_info) != 0)
	{
		minishell_errormsg(filename, strerror(errno), NULL);
		return (0);
	}
	st_mode = status_info.st_mode;
	if (errno_var == ENOENT)
		minishell_errormsg(filename, "command not found", NULL);
	else if ((07770000 & st_mode) == S_IFDIR)
		minishell_errormsg(filename, "is a directory", NULL);
	else
		minishell_errormsg(filename, strerror(errno_var), NULL);
	return (1);
}
