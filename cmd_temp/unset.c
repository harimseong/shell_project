/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:35:30 by gson              #+#    #+#             */
/*   Updated: 2022/06/09 16:16:12 by gson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static int	check_arg_error(char *argv)
{
	if (check_identifier_first(argv[0]) == -1)
	{
		printf("unset: `%s': not a valid identifier\n", argv);
		return (1);
	}
	if (is_contain_special(argv) == -1)
	{
		printf("unset: `%s': not a valid identifier\n", argv);
		return (1);
	}
	return (0);
}

int	unset_arg(t_dlist *envlist, char *argv)
{
	t_env	*cur_env;

	if (check_arg_error(argv) == 1)
		return (1);
	if (check_identifier_first(argv[0]) == 0
		&& ft_strlen(argv) == 1)
		return (0);
	envlist->cur = envlist->head;
	while (envlist->cur != 0)
	{
		cur_env = (t_env *)envlist->cur->content;
		if (ft_strcmp(cur_env->key, argv) == 0)
		{
			if (envlist->cur == envlist->head)
				pop_front(envlist, &delete_content);
			if (envlist->cur == envlist->tail)
				pop_back(envlist, &delete_content);
			else
				pop_node(envlist, envlist->cur, &delete_content);
			return (0);
		}
		envlist->cur = envlist->cur->next;
	}
	return (0);
}

int	unset(t_dlist *envlist, int argc, char **argv)
{
	int	i;
	int	status;

	status = 0;
	if (argc == 2)
		return (0);
	else if (argc > 2)
	{
		i = 2;
		while (i < argc)
		{
			if (unset_arg(envlist, argv[i]) == 1)
				status = 1;
			i++;
		}
	}
	return (status);
}
