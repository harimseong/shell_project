/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_wrapper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:15:41 by hseong            #+#    #+#             */
/*   Updated: 2022/06/16 16:29:00 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include "libft.h"
#include  <stdio.h>

#include "minishell.h"
#include "execute.h"

#define MAX_PATH (1024)

int	execve_wrapper(const char *filename, char **argv, char **envp,
	char **path_arr)
{
	char	*file_path;

	minishell_assert(ft_strlen(filename) < MAX_PATH, __FILE__, __LINE__);
	file_path = ft_strrchr(filename, '/');
	if (file_path == NULL)
		ft_execvpe(filename, argv, envp, path_arr);
	else
		execve(filename, argv, envp);
	if (errno == ENOENT)
		minishell_errormsg(filename, strerror(errno), NULL);
	else 
		minishell_errormsg("execve", strerror(errno), NULL);
	return (errno);
}
