/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:45:20 by hseong            #+#    #+#             */
/*   Updated: 2022/06/11 23:07:46 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "execute.h"
#include "minishell.h"
#include "parser/parser.h"

typedef int						(*t_redirect_func)(t_redirect *);

int			execute_command(t_dlist *word_list, t_dlist *env_list);
static int	set_redirect(t_dlist *redirect_list);
static int	close_fd(t_dlist *redirect_list);

static const t_redirect_func	g_redirect_func_tab[REDIR_NUM_OPS] = {
	redirect_in,
	redirect_out,
	redirect_append,
	redirect_heredoc
};

int	generate_process(t_dlist *word_list, t_dlist *redirect_list,
	t_dlist *env_list)
{
	int		pid;
	int		status;

	pid = 0;
	status = set_redirect(redirect_list);
	if (status == 0)
	{
		pid = fork();
		if (pid == 0)
			execute_command(word_list, env_list);
	}
	if (status != 0 || close_fd(redirect_list))
		perror("minishell");
	return (pid);
}

int	set_redirect(t_dlist *redirect_list)
{
	t_node		*node;
	t_redirect	*redirect;

	node = redirect_list->head;
	while (node != NULL)
	{
		redirect = node->content;
		g_redirect_func_tab[redirect->redir_type](redirect);
		node = node->next;
	}
	return (0);
}

int	close_fd(t_dlist *redirect_list)
{
	t_redirect	*redirect;

	redirect = get_front(redirect_list);
	while (redirect != NULL)
	{
		if (redirect->redir_type == REDIR_PROCESSED)
		{
			if (close(redirect->descriptor) < 0)
				return (1);
		}
		pop_front(redirect_list, delete_redirect_content);
		redirect = get_front(redirect_list);
	}
	return (0);
}
