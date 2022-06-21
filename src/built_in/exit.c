/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:12:01 by gson              #+#    #+#             */
/*   Updated: 2022/06/21 09:51:19 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static int	check_longlong(char *arg)
{
	int			error;
	long long	num;

	error = 0;
	num = ft_atoll(arg, &error);
	(void)num;
	if (error == -1)
		return (0);
	return (1);
}

static int	check_only_numeric(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != 0)
	{
		if (ft_isdigit(arg[i]) == 0)
		{
			if (arg[i] == '-' && i == 0)
			{
				i++;
				continue ;
			}
			else
				return (0);
		}
		i++;
	}
	return (1);
}

static long long	find_status(t_dlist *envlist)
{
	t_env		*cur_env;
	long long	status;

	status = 0;
	envlist->cur = envlist->head;
	while (envlist->cur != 0)
	{
		cur_env = (t_env *)envlist->cur->content;
		if (ft_strncmp(cur_env->key, "?\0", 2) == 0)
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

	status = find_status(envlist);
	if (argc == 2)
	{
		if (check_only_numeric(argv[1]) == 0 || check_longlong(argv[1]) == 0)
		{
			printf("minishell: exit: %s: numeric argument required\n",
				argv[1]);
			status = 255;
		}
		else
			status = ft_atoll(argv[1], NULL) % 256;
	}
	else if (argc > 2)
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	dlist_delete(envlist, &delete_content);
	exit((int)status);
}
