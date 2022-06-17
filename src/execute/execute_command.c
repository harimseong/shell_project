/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:06:41 by hseong            #+#    #+#             */
/*   Updated: 2022/06/17 20:00:01 by hseong           ###   ########.fr       */
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

int	execute_command(t_dlist *word_list, t_dlist *env_list)
{
	int		status;
	char	**argv;
	char	**envp;
	char	**path_arr;

	argv = dlist_to_array(word_list, get_word_from_token);
	envp = dlist_to_array(env_list, env_to_str);
	path_arr = ft_split(find_env_by_key(env_list, "PATH"), ":");
	status = execve_wrapper(argv[0], argv, envp, path_arr);
	free_str_arr(envp);
	free_str_arr(path_arr);
	free_str_arr(argv);
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

int	execute_builtin(t_dlist *env_list, t_dlist *word_list, int idx)
{
	int		argc;
	char	**argv;

	argc = word_list->size;
	argv = dlist_to_array(word_list, get_word_from_token);
	return (g_builtin_tab[idx](env_list, argc, argv));
}
