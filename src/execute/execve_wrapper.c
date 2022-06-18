/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_wrapper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:15:41 by hseong            #+#    #+#             */
/*   Updated: 2022/06/18 16:40:29 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include "libft.h"

#include "minishell.h"
#include "constants.h"
#include "execute.h"

int	execve_wrapper(const char *filename, char **argv, char **envp,
	char **path_arr)
{
	char	*file_path;

	minishell_assert(ft_strlen(filename) < MAX_PATHNAME, __FILE__, __LINE__);
	file_path = ft_strrchr(filename, '/');
	// access to directory leads to Permission denied error (EACCES)
	// check the name whether directory or not with stat().
	if (file_path == NULL)
		ft_execvpe(filename, argv, envp, path_arr);
	else
		execve(filename, argv, envp);
	if (errno == ENOENT)
		minishell_errormsg(filename, "command not found", NULL);
	else
		minishell_errormsg(filename, strerror(errno), NULL);
	return (errno);
}
