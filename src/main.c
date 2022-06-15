/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:00:17 by hseong            #+#    #+#             */
/*   Updated: 2022/06/15 19:50:39 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "readline/readline.h"
#include "readline/history.h"
#include <unistd.h>
#include "libft.h"

#include "minishell.h"
#include "cmd.h"
#include "parser/parser.h"

int			minishell_initialize(int argc, char **argv, char **prompt);
static void	prompt_info(t_dlist *env_list);

t_dlist		*g_env_list;

int	main(int argc, char *argv[], char *envp[])
{
	t_dlist			*pipeline_list;
	t_dlist			*env_list;
	char			*line;
	char			*prompt;

	env_list = set_envlist(envp, dlist_init());
	g_env_list = env_list;
	minishell_initialize(argc, argv, &prompt);
	while (prompt)
	{
		prompt_info(env_list);
		line = readline(prompt);
		if (line == NULL)
			builtin_print_exit(env_list, 0, NULL);
		if (ft_strlen(line) > 0)
			add_history(line);
		pipeline_list = parser(line, env_list);
		if (pipeline_list == NULL)
			continue ;
		read_pipeline(pipeline_list, env_list);
		dlist_delete(pipeline_list, delete_pipeline_content);
	}
	builtin_set_exit(env_list, 1, 0, NULL);
	return (0);
}
//				inspection tools
// opened fd:
// 				system("lsof -p $$");
// token list:
// 				dlist_print_forward(pipeline_list, pipeline_content_print);

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

void	minishell_assert(int is_true, const char *file, int line)
{
	char	*number;

	if (is_true)
		return ;
	minishell_errormsg(strerror(errno), NULL, NULL);
	if (DEBUG_FLAG == 0)
		return ;
	ft_putstr_fd("assertion: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(":", STDERR_FILENO);
	number = ft_itoa(line);
	ft_putstr_fd(number, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free(number);
}

void	prompt_info(t_dlist *env_list)
{
	if (DEBUG_FLAG)
		printf("%-4.d|", get_question(env_list));
}
