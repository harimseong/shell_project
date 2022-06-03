/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:29:37 by gson              #+#    #+#             */
/*   Updated: 2022/06/03 19:10:21 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "dlinkedlist.h"

int	builtin_export(t_dlist *envlist, int argc, char **argv)
{
	t_dlist	*cp_envlist;
	t_env	*cur_env;
	t_env	*new_env;
	t_env	*temp_env;
	char	**element;

	cp_envlist = dlist_duplicate(envlist, sizeof(t_env));
	mergesort_dlist(cp_envlist, key_compare);
	cp_envlist->cur = cp_envlist->head;
	if (argc == 1)
	{
		while (cp_envlist->cur != 0)
		{
			cur_env = (t_env *)cp_envlist->cur->content;
			if (cur_env->has_equal == 1 || cur_env->has_equal == 0)
				printf("%s=%s\n", cur_env->key, cur_env->value);
			cp_envlist->cur = cp_envlist->cur->next;
		}
	}
	else if (argc == 2)
	{
		element = ft_split(argv[1], "=");
		new_env = malloc(sizeof(t_env));
		new_env->key = element[0];
		if (element[1] != 0)
		{
			new_env->value = element[1];
			new_env->has_equal = 1;
		}
		else
		{
			new_env->value = NULL;
			new_env->has_equal = 0;
		}
		push_back(envlist, new_env);
		temp_env = envlist->tail->content;
		envlist->tail->content = envlist->tail->prev->content;
		envlist->tail->prev->content = temp_env;
	}
	return (0);
}
