/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:05:10 by gson              #+#    #+#             */
/*   Updated: 2022/06/20 01:18:22 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"

static void	set_question(t_dlist *new_env_list, int status);
static char	**find_question(t_dlist *envlist);
static int	get_question(t_dlist *envlist);

/*
 * assumes environment variable '?' is never unset.
 */
int	status_handler(int status, t_dlist *new_env_list, int type)
{
	static t_dlist	*env_list;

	if (type == SH_START)
	{
		get_env_list(new_env_list);
		env_list = new_env_list;
	}
	if (type == SH_SET)
		set_question(env_list, status);
	else if (type == SH_GET)
		return (get_question(env_list));
	return (0);
}

void	set_question(t_dlist *env_list, int status)
{
	char			**value_ptr;

	value_ptr = find_question(env_list);
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

t_dlist	*get_env_list(t_dlist *new_env_list)
{
	static t_dlist	*env_list;

	if (new_env_list != NULL)
		env_list = new_env_list;
	return (env_list);
}
