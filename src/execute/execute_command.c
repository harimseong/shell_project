/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:06:41 by hseong            #+#    #+#             */
/*   Updated: 2022/06/22 18:24:45 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

#include "minishell.h"
#include "cmd.h"
#include "constants.h"
#include "execute.h"

int	is_builtin(const char *name);
int	execute_builtin(t_dlist *env_list, t_dlist *word_list, int idx);

// envp is made of env_list which is be deallocated later.
// don't free envp.
int	execute_command(t_dlist *word_list, t_dlist *env_list)
{
	int		status;
	char	**argv;
	char	**envp;
	char	**path_arr;
	int		idx;

	idx = is_builtin(get_word_from_token(get_front(word_list)));
	if (idx > 0)
		status = execute_builtin(env_list, word_list, idx - 1);
	else
	{
		argv = dlist_to_array(word_list, get_word_from_token);
		envp = dlist_to_array(env_list, env_to_str);
		path_arr = ft_split(find_env_by_key(env_list, "PATH"), ":");
		status = execve_wrapper(argv[0], argv, envp, path_arr);
		free_str_arr(path_arr);
		free_str_arr(argv);
		free_str_arr(envp);
	}
	return (builtin_set_exit(env_list, status, 0, NULL));
}

