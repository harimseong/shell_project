/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:50:00 by gson              #+#    #+#             */
/*   Updated: 2022/05/26 20:06:27 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

t_env	*set_env(char *fullenv)
{
	t_env	*content;
	char	**key_value;

	content = malloc(sizeof(t_env));
	key_value = ft_split(fullenv, "=");
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

/*
int	main(int argc, char **argv, char *envp[])
{
	char	**cpenv;
	char	*cmd;
	t_dlist	*envlist;
	int		i;

	i = 0;
	while (envp[i] != 0)
		i++;
	cpenv = malloc((sizeof(char *) * i) + 1);
	(void)argc;
	cpenv = copy_env(cpenv, envp);
	envlist = dlist_init();
	envlist = set_envlist(cpenv, envlist);
	cmd = argv[1];
	if (ft_strcmp(cmd, "env") == 0)
		env(envlist);
	if (ft_strcmp(cmd, "export") == 0)
		export(envlist, argc, argv);
	return (0);
}
*/
