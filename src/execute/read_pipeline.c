/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 21:07:30 by hseong            #+#    #+#             */
/*   Updated: 2022/06/22 20:05:29 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "libft.h"

#include "minishell.h"
#include "constants.h"
#include "execute.h"
#include "parser/parser.h"

int
generate_process(t_command *command, t_dlist *env_list, int pipe_exist);
int
check_builtin_no_pipe(t_command *command, t_dlist *env_list);
void
handle_signals(void);

static int
read_command_list(t_dlist *command_list, t_dlist *env_list, t_dlist *pid_list);
static int
wait_process(t_dlist *pid_list);
static void
pipeline_logic_op(int pipeline_type, int *status);

void	read_pipeline(t_dlist *pipeline_list, t_dlist *env_list)
{
	t_pipeline	*pipeline;
	t_dlist		*pid_list;
	int			pipeline_type;
	int			status;

	pid_list = dlist_init();
	pipeline = get_front(pipeline_list);
	status_handler(0, NULL, SH_SET);
	status = 0;
	while (pipeline != NULL)
	{
		pipeline_type = pipeline->pipeline_type;
		if (status == 0)
		{
			pipeline->result
				= read_command_list(pipeline->command_list, env_list, pid_list);
			status_handler(pipeline->result, NULL, SH_SET);
		}
		pop_front(pipeline_list, delete_pipeline_content);
		pipeline = get_front(pipeline_list);
		pipeline_logic_op(pipeline_type, &status);
	}
	dlist_delete(pid_list, free);
}

// moved pid_list to upper function
int	read_command_list(t_dlist *command_list, t_dlist *env_list,
		t_dlist *pid_list)
{
	t_command	*command;
	pid_t		pid;
	int			flag;

	command = get_front(command_list);
	if (command_list->size == 1 && check_builtin_no_pipe(command, env_list))
		return (status_handler(0, NULL, SH_GET));
	flag = 0;
	while (command != NULL)
	{
		if (flag == CMD_HEREDOC)
		{
			pid = *((pid_t *)get_front(pid_list));
			pop_front(pid_list, free);
			waitpid(pid, NULL, 0);
		}
		pid = generate_process(command, env_list, command_list->size > 1);
		flag = command->flag;
		pop_front(command_list, delete_command_content);
		command = get_front(command_list);
		push_back(pid_list,
			ft_memcpy(malloc(sizeof(pid_t)), &pid, sizeof(pid_t)));
	}
	return (wait_process(pid_list));
}

/*
 * sequential waipid could be a problem
 */
int	wait_process(t_dlist *pid_list)
{
	int		status;
	pid_t	pid;

	status = 0;
	while (pid_list->size > 0)
	{
		pid = *((pid_t *)get_front(pid_list));
		pop_front(pid_list, free);
		if (pid < 0)
		{
			status = -pid;
			continue ;
		}
		waitpid(pid, &status, 0);
		print_msg_by_signal(pid, status);
	}
	handle_signals();
	dlist_empty(pid_list, free);
	return (WIFEXITED(status) * WEXITSTATUS(status)
		+ WIFSIGNALED(status) * (WTERMSIG(status) | 128));
}

void	pipeline_logic_op(int pipeline_type, int *status)
{
	int		last_status;

	last_status = status_handler(0, NULL, SH_GET);
	if (pipeline_type == TT_OR)
		*status = last_status == 0;
	else if (pipeline_type == TT_AND)
		*status = last_status != 0;
}

