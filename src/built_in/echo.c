/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 18:48:54 by gson              #+#    #+#             */
/*   Updated: 2022/06/15 09:29:25 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int	check_echo_flag(char *arg)
{
	int	i;
	int	arg_len;

	if (arg == NULL)
		return (0);
	i = 0;
	arg_len = ft_strlen(arg);
	if (arg[i] == '-')
	{
		i++;
		while (arg[i] == 'n')
		{
			i++;
		}
	}
	if (i == arg_len)
		return (1);
	return (0);
}

int	echo(t_dlist *envlist, int argc, char **argv)
{
	int	flag;
	int	i;

	(void)envlist;
	flag = 0;
	i = 1;
	while (i < argc && check_echo_flag(argv[i]) == 1)
	{
		flag = 1;
		i++;
	}
	while (i + 1 < argc)
		printf("%s ", argv[i++]);
	if (argv[i] != NULL)
		printf("%s", argv[i]);
	if (flag == 0)
		printf("\n");
	return (0);
}
