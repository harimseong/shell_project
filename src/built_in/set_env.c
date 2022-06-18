/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:50:00 by gson              #+#    #+#             */
/*   Updated: 2022/06/18 21:14:06 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

t_env	*set_env(char *fullenv)
{
	t_env	*content;
	char	**key_value;

	content = ft_calloc(1, sizeof(t_env));
	key_value = ft_split_first(fullenv, "=");
	content->key = key_value[0];
	if (key_value[1] != 0)
	{
		content->value = key_value[1];
		content->has_equal = 1;
	}
	else
	{
		content->value = NULL;
		content->has_equal = 0;
	}
	free(key_value);
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
	content->key = ft_strndup("?", 2);
	content->value = ft_strndup("0", 2);
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
