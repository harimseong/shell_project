/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 21:14:25 by hseong            #+#    #+#             */
/*   Updated: 2022/06/22 21:14:38 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "minishell.h"
#include "cmd.h"
#include "constants.h"
#include "execute.h"
#include "parser/parser.h"

#define BUILTIN_TAB_SIZE (7)

typedef int				(*t_program)(t_dlist *, int, char **);

int			set_redirect(t_dlist *redirect_list);
int			is_builtin(const char *name);
int			execute_builtin(t_dlist *env_list, t_dlist *word_list, int idx);

static void	close_fd(t_dlist *redirect_list);

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

int	check_builtin_no_pipe(t_command *command, t_dlist *env_list)
{
	int		idx;

	if (command->word_list->size < 1)
		return (0);
	idx = is_builtin(get_word_from_token(get_front(command->word_list)));
	if (idx == 0)
		return (0);
	if (set_redirect(command->redirect_list) == 0)
		status_handler(execute_builtin(env_list, command->word_list, idx - 1),
			NULL, SH_SET);
	close_fd(command->redirect_list);
	minishell_assert(dup2(MINISHELL_STDIN, STDIN_FILENO) > -1,
		__FILE__, __LINE__);
	minishell_assert(dup2(MINISHELL_STDOUT, STDOUT_FILENO) > -1,
		__FILE__, __LINE__);
	return (1);
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

void	close_fd(t_dlist *redirect_list)
{
	t_node		*redirect_node;
	t_redirect	*redirect_content;

	redirect_node = redirect_list->head;
	while (redirect_node != NULL)
	{
		redirect_content = redirect_node->content;
		if (redirect_content->descriptor < 0)
			break ;
		minishell_assert(close(redirect_content->descriptor) == 0,
			__FILE__, __LINE__);
		redirect_node = redirect_node->next;
	}
}
