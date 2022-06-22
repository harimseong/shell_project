/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helper_func_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:22:19 by hseong            #+#    #+#             */
/*   Updated: 2022/06/22 19:41:49 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "execute.h"
#include <sys/wait.h>
#include <unistd.h>

static const char	*g_signal_tab[]
	= {
	"	hangup",
	"",
	"	quit",
	"	signaled: 4",
	"	signaled: 5",
	"	abort",
	"	signaled: 7",
	"	signaled: 8",
	"	killed",
	"	signaled: 10",
	"	signaled: 11",
	"	signaled: 12",
	"	signaled: 13",
	"	signaled: 14",
	"	terminated",
	"	signaled"
};

// IFS: Internal Field Seperator
int	is_ifs(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

void	print_msg_by_signal(int pid, int status)
{
	char	*pid_str;
	char	*status_str;

	if (!WIFSIGNALED(status) || WTERMSIG(status) > 3 || WTERMSIG(status) == 2)
		return ;
	status = WTERMSIG(status);
	pid_str = ft_itoa(pid);
	ft_putstr_fd("\t", STDERR_FILENO);
	ft_putstr_fd(pid_str, STDERR_FILENO);
	if (status < 16)
	{
		ft_putstr_fd(g_signal_tab[status - 1], STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else
	{
		status_str = ft_itoa(status);
		ft_putstr_fd(g_signal_tab[15], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(status_str, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		free(status_str);
	}
	free(pid_str);
}
