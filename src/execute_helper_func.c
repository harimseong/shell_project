/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helper_func.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 22:30:30 by hseong            #+#    #+#             */
/*   Updated: 2022/06/09 22:30:53 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "parser/token.h"
#include "execute.h"

void	*get_word_from_token(void *content)
{
	t_token	*token;
	
	token = content;
	return (token->word);
}

void	*get_key_from_env(void *content)
{
	t_env	*env;

	env = content;
	return (env->key);
}
