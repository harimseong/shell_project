/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:53:26 by gson              #+#    #+#             */
/*   Updated: 2022/06/18 19:16:54 by gson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static int	find_pwd(t_dlist *envlist)
{
	t_env	*cur_env;

	envlist->cur = envlist->head;
	while (envlist->cur != 0)
	{
		cur_env = (t_env *)envlist->cur->content;
		if (ft_strcmp(cur_env->key, "PWD") == 0)
			return (1);
		envlist->cur = envlist->cur->next;
	}
	return (0);
}

static int	find_oldpwd(t_dlist *envlist)
{
	t_env	*cur_env;

	envlist->cur = envlist->head;
	while (envlist->cur != 0)
	{
		cur_env = (t_env *)envlist->cur->content;
		if (ft_strcmp(cur_env->key, "OLDPWD") == 0)
			return (1);
		envlist->cur = envlist->cur->next;
	}
	return (0);
}

static char	*set_pwd(t_dlist *envlist)
{
	t_env	*cur_env;
	char	*oldpwd;

	envlist->cur = envlist->head;
	while (envlist->cur != 0)
	{
		cur_env = (t_env *)envlist->cur->content;
		if (ft_strcmp(cur_env->key, "PWD") == 0)
		{
			oldpwd = ft_strdup(cur_env->value);
			cur_env->value = getcwd(NULL, 0);
		}
		envlist->cur = envlist->cur->next;
	}
	return (oldpwd);
}

static void	set_oldpwd(t_dlist *envlist, char *oldpwd)
{
	t_env	*cur_env;

	envlist->cur = envlist->head;
	while (envlist->cur != 0)
	{
		cur_env = (t_env *)envlist->cur->content;
		if (ft_strcmp(cur_env->key, "OLDPWD") == 0)
			cur_env->value = oldpwd;
		envlist->cur = envlist->cur->next;
	}
}

void	set_env_pwd(t_dlist *envlist, char *oldpwd)
{
	t_env	*new_env;

	if (find_pwd(envlist) == 1)
		oldpwd = set_pwd(envlist);
	else
	{
		new_env = malloc(sizeof(t_env));
		new_env->key = "PWD";
		new_env->value = getcwd(NULL, 0);
		new_env->has_equal = 1;
		push_back(envlist, new_env);
	}
	if (find_oldpwd(envlist) == 1)
		set_oldpwd(envlist, oldpwd);
	else
	{
		new_env = malloc(sizeof(t_env));
		new_env->key = "OLDPWD";
		new_env->value = oldpwd;
		new_env->has_equal = 1;
		push_back(envlist, new_env);
	}
}
