/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:00:17 by hseong            #+#    #+#             */
/*   Updated: 2022/06/14 16:08:09 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "libft.h"

#include "minishell.h"
#include "cmd.h"
#include "parser/parser.h"

int	minishell_initialize(int argc, char **argv, char **prompt);

int	main(int argc, char *argv[], char *envp[])
{
	t_dlist		*pipeline_list;
	t_dlist		*env_list;
	char		*line;
	char		*prompt;

	pipeline_list = (void *)1;
	env_list = set_envlist(envp, dlist_init());
	prompt = NULL;
	minishell_initialize(argc, argv, &prompt);
	while (prompt)
	{
		line = readline(prompt);
		if (line == NULL)
			break ;
		pipeline_list = parser(line, env_list);
		if (pipeline_list == NULL)
			continue ;
		add_history(line);
//		dlist_print_forward(pipeline_list, pipeline_content_print);
		read_pipeline(pipeline_list, env_list);
//		system("lsof -p $$");
		dlist_delete(pipeline_list, delete_pipeline_content);
//		system("leaks minishell");
	}
// 	free env_list in Ctrl-D signal handler
//		+ prompt
	return (0);
}

void	minishell_errormsg(const char *s1, const char *s2, const char *s3)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (s1 != NULL)
		ft_putstr_fd(s1, STDERR_FILENO);
	if (s2 != NULL)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(s2, STDERR_FILENO);
	}
	if (s3 != NULL)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(s3, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	minishell_assertion(int is_true, const char *file, int line)
{
	char	*number;

	if (DEBUG_FLAG == 0)
		return ;
	if (is_true)
		return ;
	minishell_errormsg(strerror(errno), NULL, NULL);
	ft_putstr_fd("assertion: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(":", STDERR_FILENO);
	number = ft_itoa(line);
	ft_putstr_fd(number, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free(number);
}
