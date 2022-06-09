/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 18:48:54 by gson              #+#    #+#             */
/*   Updated: 2022/06/03 14:20:46 by gson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int	check_echo_flag(char *arg)
{
	int	i;
	int	arg_len;

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

int	echo(char **argv)
{
	int	flag;
	int	i;

	flag = 0;
	i = 2;
	while (check_echo_flag(argv[i]) == 1)
	{
		flag = 1;
		i++;
	}
	while (argv[i + 1] != 0)
	{
		printf("%s ", argv[i]);
		i++;
	}
	printf("%s", argv[i]);
	if (flag == 0)
		printf("\n");
	return (0);
}
