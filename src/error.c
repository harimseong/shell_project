/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 07:14:06 by hseong            #+#    #+#             */
/*   Updated: 2022/06/21 07:15:29 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "minishell.h"
#include "constants.h"

void	minishell_errormsg(const char *s1, const char *s2, const char *s3)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (s1 != NULL)
		ft_putstr_fd(s1, STDERR_FILENO);
	if (s2 != NULL)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(s2, STDERR_FILENO);
	}
	if (s3 != NULL)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(s3, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
}

int	minishell_assert(int is_true, const char *file, int line)
{
	char	*number;

	if (is_true)
		return (0);
	minishell_errormsg(strerror(errno), NULL, NULL);
	if (DEBUG_FLAG == 0)
		return (1);
	ft_putstr_fd("assertion: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(":", STDERR_FILENO);
	number = ft_itoa(line);
	ft_putstr_fd(number, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free(number);
	return (1);
}
