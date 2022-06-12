/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:06:41 by hseong            #+#    #+#             */
/*   Updated: 2022/06/12 20:42:29 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

#include "minishell.h"
#include "constants.h"
#include "cmd.h"
#include "execute.h"

typedef int			(*t_program)(t_dlist *, int, char **);

static int	is_builtin(const char *name);
static int	execute_builtin(t_dlist *env_list, char **argv, int idx);

static const int	g_builtin_tab_size = 7;
static const char	*g_builtin_name_tab[] = {
	NULL,
	"cd",
	"echo",
	"env",
	"exit",
	"export",
	"pwd",
	"unset"
};
static const t_program	g_builtin_tab[7] = {
	cd,
	echo,
	env,
	builtin_exit,
	export,
	NULL,
	unset
};

int	execute_command(t_dlist *word_list, t_dlist *env_list)
{
	int		idx;
	int		status;
	char	**argv;
	char	**envp;
	char	**path_arr;

	argv = dlist_to_array(word_list, get_word_from_token);
	idx = is_builtin(argv[0]);
	if (idx)
		status = execute_builtin(env_list, argv, idx - 1);
	else
	{
		path_arr = ft_split(get_value_from_env(env_list, "PATH"), ":");
		envp = dlist_to_array(env_list, env_to_str);
		status = ft_execvpe(argv[0], argv, envp, path_arr);
		free(envp);
		free_path_arr(path_arr);
	}
	if (status == ENOENT)
		minishell_errormsg(argv[0], "command not found", NULL);
	else if (status != 0)
		perror("minishell");
	free(argv);
	builtin_exit(env_list, 1, NULL);
	return (status);
}

int	is_builtin(const char *name)
{
	int		idx;

	idx = 1;
	while (idx < g_builtin_tab_size)
	{
		if (ft_strncmp(name, g_builtin_name_tab[idx],
			ft_strlen(g_builtin_name_tab[idx]) + 1) == 0)
			return (idx);
		++idx;
	}
	return (0);
}

int	execute_builtin(t_dlist *env_list, char **argv, int idx)
{
	int		argc;

	argc = 0;
	while (argv[argc] != NULL)
		++argc;
	return (g_builtin_tab[idx](env_list, argc, argv));
}
