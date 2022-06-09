/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:06:41 by hseong            #+#    #+#             */
/*   Updated: 2022/06/09 18:23:12 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/parser.h"

static void	execute_cmd(t_dlist *pipeline_list, t_dlist *env_list);

void	execute_pipeline(t_dlist *pipeline_list, t_dlist *env_list)
{
	t_pipeline	*pipeline;

	pipeline = pipeline_list->head->content;
	execute_cmd(pipeline->command_list, env_list);
}

void	execute_cmd(t_dlist *command_list, t_dlist *env_list)
{
	t_command	*command;

	command = command_list->head->content;
}
