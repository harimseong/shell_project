/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 21:07:30 by hseong            #+#    #+#             */
/*   Updated: 2022/06/21 02:35:29 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"

#include "minishell.h"
#include "cmd.h"
#include "constants.h"
#include "execute.h"
#include "parser/parser.h"

int
generate_process(t_command *command, t_dlist *env_list, int pipe_exist);
int
is_builtin(const char *name);
int
execute_builtin(t_dlist *env_list, t_dlist *word_list, int idx);

static int
read_command_list(t_dlist *command_list, t_dlist *env_list, t_dlist *pid_list);
static int
wait_process(t_dlist *pid_list);
static void
pipeline_logic_op(int pipeline_type, int *status);
static int
check_builtin(t_dlist *word_list);

extern t_dlist	*g_env_list;

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
		if (status != 0)
		{
			pipeline->result
				= read_command_list(pipeline->command_list, env_list, pid_list);
			status_handler(pipeline->result, NULL, SH_SET);
		}
		pop_front(pipeline_list, delete_pipeline_content);
		pipeline = get_front(pipeline_list);
		pipeline_logic_op(pipeline_type, &status);
		pipeline_type = pipeline->pipeline_type;
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
	flag = check_builtin(command->word_list);
	if (flag > 0 && command_list->size == 1)
		return (execute_builtin(env_list, command->word_list, flag - 1));
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

int	check_builtin(t_dlist *word_list)
{
	if (word_list->size == 0)
		return (0);
	return (is_builtin(get_word_from_token(get_front(word_list))));
}
