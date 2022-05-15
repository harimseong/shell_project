/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 19:22:33 by gson              #+#    #+#             */
/*   Updated: 2022/05/13 20:19:43 by gson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

static int	exit_cd(char **cwd, int status)
{
	if (status == 1)
	{
		perror("Error");
		return (1);
	}
	else if (status == 0)
		return (0);
}

int	cd(char *path)
{
	char	*cwd;
	DIR		*directory;
	char	*home_path;

	cwd = NULL;
	home_path = getenv("HOME");
	directory = opendir(path);
	if (directory == NULL)
		return (exit_cd(&cwd, 1));
	else if (closedir(directory) != 0)
		return (exit_cd(&cwd, 1));
	else if (chdir(path) != 0)
		return (exit_cd(&cwd, 1));
	cwd = getcwd(cwd, 0);
	return (0);
}
