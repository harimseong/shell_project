/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 18:24:02 by gson              #+#    #+#             */
/*   Updated: 2022/05/26 20:12:36 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int	builtin_env(t_dlist *envlist)
{
	t_env	*cur_env;

	envlist->cur = envlist->head;
	while (envlist->cur != 0)
	{
		cur_env = (t_env *)envlist->cur->content;
		if (cur_env->has_equal == 1)
			printf("%s=%s\n", cur_env->key, cur_env->value);
		envlist->cur = envlist->cur->next;
	}
	return (0);
}
