/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_directory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:25:06 by gson              #+#    #+#             */
/*   Updated: 2022/06/18 19:19:53 by gson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int	move_directory_old(t_dlist *envlist, const char *path)
{
	if (ft_strcmp(path, "-") == 0)
	{
		printf("minishell: cd: OLDPWD not set\n");
		return (1);
	}
	if (chdir(path) == -1)
	{
		printf("minishell: cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	printf("%s\n", getcwd(NULL, 0));
	set_env_pwd(envlist, NULL);
	return (0);
}

int	move_directory(t_dlist *envlist, const char *path)
{
	char	*oldpwd;

	if (ft_strcmp(path, "-") == 0)
	{
		printf("minishell: cd: OLDPWD not set\n");
		return (1);
	}
	oldpwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		printf("minishell: cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	set_env_pwd(envlist, oldpwd);
	return (0);
}
