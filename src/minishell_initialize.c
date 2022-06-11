/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_initialize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 21:31:07 by hseong            #+#    #+#             */
/*   Updated: 2022/06/11 21:57:30 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static const char	*g_default_prompt = " $> ";

char	*minishell_initialize(int argc, char **argv)
{
	char	*prompt;
	char	*front;

	(void)argc;
	(void)argv;
	front = getenv("MAIL");
	if (front == NULL)
		front = getenv("USER");
	prompt = ft_strjoin(front, g_default_prompt);
	return (prompt);
}
