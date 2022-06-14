/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_question.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:05:10 by gson              #+#    #+#             */
/*   Updated: 2022/06/14 22:52:04 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"

void	set_question(t_dlist *envlist, int status)
{
	t_env	*cur_env;

	envlist->cur = envlist->head;
	while (envlist->cur != 0)
	{
		cur_env = (t_env *)envlist->cur->content;
		if (ft_strcmp(cur_env->key, "?") == 0)
		{
			cur_env->value = ft_itoa(status);
			return ;
		}
		envlist->cur = envlist->cur->next;
	}
}

int	find_question(t_dlist *envlist)
{
	t_env	*cur_env;

	envlist->cur = envlist->head;
	while (envlist->cur != 0)
	{
		cur_env = (t_env *)envlist->cur->content;
		if (ft_strcmp(cur_env->key, "?") == 0)
			return (ft_atoi(cur_env->value));
		envlist->cur = envlist->cur->next;
	}
	return (0);
}
