/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:06:41 by hseong            #+#    #+#             */
/*   Updated: 2022/06/09 23:18:59 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlinkedlist.h"
#include "libft.h"
#include "minishell.h"
#include "cmd.h"
#include "execute.h"
#include "parser/parser.h"

static int	process_command_list(t_dlist *command_list, t_dlist *env_list);
static int	execute_command(t_dlist *word_list, t_dlist *redirect_list,
		t_dlist *env_list);

void	process_pipeline(t_dlist *pipeline_list, t_dlist *env_list)
{
	t_pipeline	*pipeline;

	pipeline = get_front(pipeline_list);
	while (pipeline != NULL)
	{
		pipeline->result
			= process_command_list(pipeline->command_list, env_list);
		pop_front(pipeline_list, delete_pipeline_content);
		pipeline = get_front(pipeline_list);
	}
}

int	process_command_list(t_dlist *command_list, t_dlist *env_list)
{
	t_command	*command;
	t_dlist		*pid_list;
//	int			*pid_ptr;

	pid_list = dlist_init();
	command = get_front(command_list);
	while (command != NULL)
	{
		execute_command(command->word_list, command->redirect_list, env_list);
		pop_front(command_list, delete_command_content);
		command = get_front(command_list);
	}
	dlist_delete(pid_list, free);
	return (0);
}

int	execute_command(t_dlist *word_list, t_dlist *redirect_list,
		t_dlist *env_list)
{
	int		pid;
	char	**argv;
	char	**envp;

	(void)redirect_list;
	pid = fork();
	if (pid != 0)
		return (pid);
	argv = dlist_to_array(word_list, get_word_from_token);
	envp = dlist_to_array(env_list, get_key_from_env);
	ft_execvpe(argv[0], argv, envp);
	dlist_delete(word_list, delete_word_content);
	dlist_delete(env_list, delete_env_content);
	free(argv);
	free(envp);
	return (0);
}
