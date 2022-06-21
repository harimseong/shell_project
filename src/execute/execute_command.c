/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:06:41 by hseong            #+#    #+#             */
/*   Updated: 2022/06/21 16:40:43 by gson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

#include "minishell.h"
#include "cmd.h"
#include "constants.h"
#include "execute.h"

#define BUILTIN_TAB_SIZE (7)

typedef int				(*t_program)(t_dlist *, int, char **);

int	is_builtin(const char *name);
int	execute_builtin(t_dlist *env_list, t_dlist *word_list, int idx);

static const char		*g_builtin_name_tab[BUILTIN_TAB_SIZE]
	= {
	"cd",
	"exit",
	"unset",
	"export",
	"echo",
	"env",
	"pwd",
};

static const t_program	g_builtin_tab[BUILTIN_TAB_SIZE]
	= {
	cd,
	builtin_exit,
	unset,
	export,
	echo,
	env,
	pwd
};

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

int	is_builtin(const char *name)
{
	int		idx;

	idx = 0;
	while (idx < BUILTIN_TAB_SIZE)
	{
		if (ft_strncmp(name, g_builtin_name_tab[idx],
				ft_strlen(g_builtin_name_tab[idx]) + 1) == 0)
			return (idx + 1);
		++idx;
	}
	return (0);
}

// argv is made of word_list which is be deallocated later.
// don't free argv.
int	execute_builtin(t_dlist *env_list, t_dlist *word_list, int idx)
{
	int		argc;
	char	**argv;
	int		status;

	argc = word_list->size;
	argv = dlist_to_array(word_list, get_word_from_token);
	status = g_builtin_tab[idx](env_list, argc, argv);
	free(argv);
	return (status);
}
