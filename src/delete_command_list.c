/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_command_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 21:26:37 by hseong            #+#    #+#             */
/*   Updated: 2022/06/09 23:13:25 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "dlinkedlist.h"
#include "minishell.h"
#include "cmd.h"
#include "parser/parser.h"

void	pipeline_content_delete(void *pipeline_arg)
{
	if (((t_pipeline *)pipeline_arg)->command_list != NULL)
		dlist_delete(((t_pipeline *)pipeline_arg)->command_list,
			delete_command_content);
	free(pipeline_arg);
}

void	command_content_delete(void *command_arg)
{
	if (((t_command *)command_arg)->word_list != NULL)
		dlist_delete(((t_command *)command_arg)->word_list,
			delete_word_content);
	if (((t_command *)command_arg)->redirect_list != NULL)
		dlist_delete(((t_command *)command_arg)->redirect_list,
			delete_redirect_content);
	free(command_arg);
}

void	word_content_delete(void *token_arg)
{
	free(((t_token *)token_arg)->word);
	free(token_arg);
}

void	redirect_content_delete(void *redirect_arg)
{
	t_redirect	*redirect;

	redirect = redirect_arg;
	free(redirect->token_set[0]->word);
	free(redirect->token_set[1]->word);
	free(redirect);
}

void	delete_env_content(void *env_arg)
{
	t_env	*env;

	env = env_arg;
	free(env->key);
	free(env->value);
	free(env);
}
