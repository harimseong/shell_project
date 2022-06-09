/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:50:00 by gson              #+#    #+#             */
/*   Updated: 2022/06/03 17:31:59 by gson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

t_env	*set_env(char *fullenv)
{
	t_env	*content;
	char	**key_value;

	content = malloc(sizeof(t_env));
	key_value = ft_split_first(fullenv, "=");
	content->key = ft_strdup(key_value[0]);
	if (key_value[1] != 0)
	{
		content->value = ft_strdup(key_value[1]);
		content->has_equal = 1;
	}
	else
	{
		content->value = NULL;
		content->has_equal = 0;
	}
	return (content);
}

t_dlist	*set_envlist(char **cpenv, t_dlist *envlist)
{
	t_env	*content;
	int		i;

	i = 0;
	while (cpenv[i] != 0)
	{
		content = set_env(cpenv[i]);
		push_back(envlist, content);
		i++;
	}
	content = malloc(sizeof(t_env));
	content->key = ft_strdup("?");
	content->value = ft_strdup("0");
	content->has_equal = -1;
	push_back(envlist, content);
	return (envlist);
}

char	**copy_env(char	**cpenv, char **envp)
{
	int		i;

	i = 0;
	while (envp[i] != 0)
	{
		cpenv[i] = ft_strdup(envp[i]);
		i++;
	}
	cpenv[i] = 0;
	return (cpenv);
}

int	main(int argc, char **argv, char *envp[])
{
	char	**cpenv;
	char	*cmd;
	t_dlist	*envlist;
	int		i;
	int		status;

	i = 0;
	status = 0;
	while (envp[i] != 0)
		i++;
	cpenv = malloc((sizeof(char *) * i) + 1);
	(void)argc;
	cpenv = copy_env(cpenv, envp);
	envlist = dlist_init();
	envlist = set_envlist(cpenv, envlist);
	cmd = argv[1];
	if (ft_strcmp(cmd, "echo") == 0)
		status = echo(argv);
	if (ft_strcmp(cmd, "env") == 0)
		status = env(envlist, argc, argv);
	if (ft_strcmp(cmd, "export") == 0)
		status = export(envlist, argc, argv);
	if (ft_strcmp(cmd, "cd") == 0)
		status = cd(envlist, argc, argv);
	if (ft_strcmp(cmd, "unset") == 0)
		status = unset(envlist, argc, argv);
	if (ft_strcmp(cmd, "exit") == 0)
		builtin_exit(envlist, argc, argv);
	return (status);
}
