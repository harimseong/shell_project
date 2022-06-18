/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:53:26 by gson              #+#    #+#             */
/*   Updated: 2022/06/18 21:31:56 by hseong           ###   ########.fr       */
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
	oldpwd = NULL;
	while (envlist->cur != 0)
	{
		cur_env = (t_env *)envlist->cur->content;
		if (ft_strcmp(cur_env->key, "PWD") == 0)
		{
			oldpwd = ft_strdup(cur_env->value);
			free(cur_env->value);
			cur_env->value = getcwd(NULL, 0);
			return (oldpwd);
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
		{
			free(cur_env->value);
			cur_env->value = oldpwd;
			return ;
		}
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
		new_env->key = ft_strndup("PWD", 3);
		new_env->value = getcwd(NULL, 0);
		new_env->has_equal = 1;
		push_back(envlist, new_env);
	}
	if (find_oldpwd(envlist) == 1)
		set_oldpwd(envlist, oldpwd);
	else
	{
		new_env = malloc(sizeof(t_env));
		new_env->key = ft_strndup("OLDPWD", 6);
		new_env->value = oldpwd;
		new_env->has_equal = 1;
		push_back(envlist, new_env);
	}
}
