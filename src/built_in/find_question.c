/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_question.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:05:10 by gson              #+#    #+#             */
/*   Updated: 2022/06/15 18:00:46 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"

void	set_question(t_dlist *envlist, int status)
{
	char	**value_ptr;

	value_ptr = find_question(envlist);
	free(*value_ptr);
	*value_ptr = ft_itoa(status);
}

char	**find_question(t_dlist *envlist)
{
	t_env	*cur_env;

	envlist->cur = envlist->head;
	while (envlist->cur != 0)
	{
		cur_env = (t_env *)envlist->cur->content;
		if (ft_strncmp(cur_env->key, "?", 2) == 0)
			return (&cur_env->value);
		envlist->cur = envlist->cur->next;
	}
	return (0);
}

int	get_question(t_dlist *envlist)
{
	return (ft_atoi(*find_question(envlist)));
}
