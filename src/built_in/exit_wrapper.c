/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_wrapper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 02:54:44 by hseong            #+#    #+#             */
/*   Updated: 2022/06/23 21:43:24 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "libft.h"

#include "minishell.h"

int	builtin_print_exit(t_dlist *env_list, int argc, char **argv)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	builtin_exit(env_list, argc, argv);
	return (0);
}

int	builtin_set_exit(t_dlist *env_list, int status, int argc, char **argv)
{
	status_handler(status, NULL, SH_SET);
	builtin_exit(env_list, argc, argv);
	return (0);
}
