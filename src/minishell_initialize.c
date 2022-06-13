/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_initialize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 21:31:07 by hseong            #+#    #+#             */
/*   Updated: 2022/06/13 16:00:10 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

#include "minishell.h"
#include "constants.h"

static int	set_prompt(char **prompt);
static int	find_option(const char *name);
static int	find_arg(const char *name);

static const char	*g_default_prompt = " $> ";

int	minishell_initialize(int argc, char **argv, char **prompt)
{
	int		idx;
	int		found_option;
	int		found_arg;

	if (argc == 1)
	{
		set_prompt(prompt);
		return (0);
	}
	idx = 0;
	while (argv[idx] != NULL)
	{
		found_option = find_option(argv[idx]);
		found_arg = find_arg(argv[idx]);
		if (found_option == FALSE && found_arg == FALSE)
		{
			if (found_option == FALSE)
				minishell_errormsg(argv[idx], "invaild option",  NULL);
			else
				minishell_errormsg(NULL, NULL, NULL);
			return (1);
		}
		++idx;
	}
	return (0);
}

int	find_option(const char *name)
{
	int		comp_len;

	comp_len = ft_strlen(name);
	if (comp_len < 2)
		comp_len = 2;
	if (ft_strncmp(name, "-c", comp_len) == 0)
		return (TRUE);
	else if (name[0] == '-')
		return (FALSE);
	return (TRUE);
}

int	find_arg(const char *name)
{
	(void)name;
	return (0);
}

int	set_prompt(char **prompt)
{
	char	*front;

	front = getenv("USER");
	*prompt = ft_strjoin(front, g_default_prompt);
	return (0);
}
