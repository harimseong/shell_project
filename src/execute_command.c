/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:06:41 by hseong            #+#    #+#             */
/*   Updated: 2022/06/10 23:16:10 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

#include "minishell.h"
#include "cmd.h"
#include "execute.h"
#include "parser/parser.h"

int	execute_command(t_dlist *word_list, t_dlist *redirect_list,
		t_dlist *env_list)
{
	int		pid;
	int		status;
	char	**argv;
	char	**envp;

	(void)redirect_list;
	pid = fork();
	if (pid != 0)
		return (pid);
	argv = dlist_to_array(word_list, get_word_from_token);
	envp = dlist_to_array(env_list, get_key_from_env);
//	if (is_builtin(argv[0]))
//		status = execute_builtin(argv[0], argv, envp);	
//	else
		status = ft_execvpe(argv[0], argv, envp);
	dlist_delete(env_list, delete_env_content);
	free(argv);
	free(envp);
	return (status);
}
