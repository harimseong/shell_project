/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_initialize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 21:31:07 by hseong            #+#    #+#             */
/*   Updated: 2022/06/11 22:50:59 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	set_prompt(char **prompt);

static const char	*g_default_prompt = " $> ";

int	minishell_initialize(int argc, char **argv, char **prompt)
{
	(void)argc;
	(void)argv;
	set_prompt(prompt);
	return (0);
}

int	set_prompt(char **prompt)
{
	char	*front;

	front = getenv("USER");
	*prompt = ft_strjoin(front, g_default_prompt);
	return (0);
}
