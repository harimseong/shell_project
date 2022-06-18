/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 13:30:48 by gson              #+#    #+#             */
/*   Updated: 2022/06/14 23:00:41 by gson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int	is_contain_special(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (ft_isalnum(str[i]) || (str[i] == '_'))
			i++;
		else
			return (-1);
	}
	return (0);
}

int	check_identifier_first(char identifier)
{
	if (identifier == '_')
		return (0);
	if (ft_isalpha(identifier))
		return (1);
	return (-1);
}

static void	make_env(t_env *cur_env, char **element, char *argv)
{
	if (element[1] != 0)
	{
		cur_env->value = element[1];
		cur_env->has_equal = 1;
	}
	else if (ft_strchr(argv, '=') == NULL)
	{
		cur_env->value = NULL;
		cur_env->has_equal = 0;
	}
	else
	{
		cur_env->value = NULL;
		cur_env->has_equal = 1;
	}
}

int	check_key_dup(t_dlist *envlist, char **element, char *argv)
{
	t_env	*cur_env;

	envlist->cur = envlist->head;
	while (envlist->cur != 0)
	{
		cur_env = (t_env *)envlist->cur->content;
		if (ft_strcmp(cur_env->key, element[0]) == 0)
		{
			if (ft_strchr(argv, '=') == NULL)
				return (1);
			make_env(cur_env, element, argv);
			return (1);
		}
		envlist->cur = envlist->cur->next;
	}
	return (0);
}
