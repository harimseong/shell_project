/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 18:24:02 by gson              #+#    #+#             */
/*   Updated: 2022/06/11 16:49:43 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static int	check_arg_error(int argc, char **argv)
{
	if (argc > 1)
	{
		printf("env: %s: No such file or directory\n", argv[1]);
		return (1);
	}
	return (0);
}

int	env(t_dlist *envlist, int argc, char **argv)
{
	t_env	*cur_env;

	if (check_arg_error(argc, argv) == 1)
		return (1);
	envlist->cur = envlist->head;
	while (envlist->cur != 0)
	{
		cur_env = (t_env *)envlist->cur->content;
		if (cur_env->has_equal == 1)
		{
			if (cur_env->value == NULL)
				printf("%s=\n", cur_env->key);
			else
				printf("%s=%s\n", cur_env->key, cur_env->value);
		}
		envlist->cur = envlist->cur->next;
	}
	return (0);
}

void	*copy_env_content(void *content)
{
	t_env	*old_env;
	t_env	*new_env;

	old_env = content;
	new_env = ft_calloc(1, sizeof(t_env));
	new_env->key = ft_strndup(old_env->key, ft_strlen(old_env->key));
	if (old_env->value != NULL)
		new_env->value = ft_strndup(old_env->value, ft_strlen(old_env->value));
	new_env->has_equal = old_env->has_equal;
	return (new_env);
}
