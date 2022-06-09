/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:12:01 by gson              #+#    #+#             */
/*   Updated: 2022/06/03 18:27:51 by gson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int	check_longlong(char *arg)
{
	int			error;
	long long	num;

	error = 0;
	num = ft_atoll(arg, &error);
	if (error == -1)
		return (0);
	return (1);
}

int	check_only_numeric(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != 0)
	{
		if (ft_isdigit(arg[i]) == 0)
		{
			if (arg[i] == '-' && i == 0)
				continue ;
			else
				return (0);
		}
		i++;
	}
	return (1);
}

long long	find_status(t_dlist *envlist)
{
	t_env		*cur_env;
	long long	status;

	status = 0;
	envlist->cur = envlist->head;
	while (envlist->cur != 0)
	{
		cur_env = (t_env *)envlist->cur->content;
		if (ft_strcmp(cur_env->key, "?") == 0)
		{
			status = ft_atoll(cur_env->value, NULL);
			return (status);
		}
		envlist->cur = envlist->cur->next;
	}
	return (status);
}

int	builtin_exit(t_dlist *envlist, int argc, char **argv)
{
	long long	status;
	int			i;

	status = find_status(envlist);
	i = 0;
	if (argc == 3)
	{
		if (check_only_numeric(argv[2]) == 0 || check_longlong(argv[2]) == 0)
		{
			printf("minishell: exit: `%s': numeric argument required\n",
				argv[2]);
			status = 255;
		}
		else
			status = ft_atoll(argv[2], NULL) / 256;
	}
	else if (argc > 3)
	{
		printf("minishell: exit: too many arguments\n");
		status = 1;
	}
	delete_dlist(envlist, &delete_content);
	exit((int)status);
}
