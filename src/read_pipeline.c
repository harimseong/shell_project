/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 21:07:30 by hseong            #+#    #+#             */
/*   Updated: 2022/06/11 05:32:40 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "libft.h"

#include "minishell.h"
#include "cmd.h"
#include "parser/parser.h"

int	execute_command(t_dlist *word_list, t_dlist *redirect_list,
	t_dlist *env_list);
static int	read_command_list(t_dlist *command_list, t_dlist *env_list);
static int	wait_process(t_dlist *pid_list);

void	read_pipeline(t_dlist *pipeline_list, t_dlist *env_list)
{
	t_pipeline	*pipeline;

	pipeline = get_front(pipeline_list);
	while (pipeline != NULL)
	{
		pipeline->result
			= read_command_list(pipeline->command_list, env_list);
		pop_front(pipeline_list, delete_pipeline_content);
		pipeline = get_front(pipeline_list);
	}
}

int	read_command_list(t_dlist *command_list, t_dlist *env_list)
{
	t_command	*command;
	t_dlist		*pid_list;
	pid_t		pid;
	int			status;

	pid_list = dlist_init();
	command = get_front(command_list);
	while (command != NULL)
	{
		pid = fork();
		if (pid == 0)
			execute_command(command->word_list,
			command->redirect_list, env_list);
		pop_front(command_list, delete_command_content);
		command = get_front(command_list);
		push_back(pid_list,
			ft_memcpy(malloc(sizeof(pid_t)), &pid, sizeof(pid_t)));
	}
	status = wait_process(pid_list);
	dlist_delete(pid_list, free);
	return (status);
}

int	wait_process(t_dlist *pid_list)
{
	int		status;
	pid_t	*pid_ptr;

	while (pid_list->size > 0)
	{
		pid_ptr = get_front(pid_list);
		waitpid(*pid_ptr, &status, 0);
		pop_front(pid_list, free);
	}
	return (status);
}
