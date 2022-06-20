/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:00:17 by hseong            #+#    #+#             */
/*   Updated: 2022/06/20 23:23:07 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "readline/readline.h"
#include "readline/history.h"
#include "libft.h"

#include "minishell.h"
#include "cmd.h"
#include "parser/parser.h"

int			minishell_initialize(int argc, char **argv, t_dlist *env_list,
				char **prompt);
static void	prompt_info(t_dlist *env_list);

int	main(int argc, char *argv[], char *envp[])
{
	t_dlist			*pipeline_list;
	t_dlist			*env_list;
	char			*line;
	char			*prompt;

	env_list = set_envlist(envp, dlist_init());
	status_handler(0, env_list, SH_START);
	if (minishell_initialize(argc, argv, env_list, &prompt))
		builtin_exit(env_list, 0, NULL);
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
		free(line);
	}
	return (1);
}
//				inspection tools
// opened fd:
// 				system("lsof -p $$");
// token list:
// 				dlist_print_forward(pipeline_list, pipeline_content_print);
// leak check:
// 				system("leaks minishell");

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

int	minishell_assert(int is_true, const char *file, int line)
{
	char	*number;

	if (is_true)
		return (0);
	minishell_errormsg(strerror(errno), NULL, NULL);
	if (DEBUG_FLAG == 0)
		return (1);
	ft_putstr_fd("assertion: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(":", STDERR_FILENO);
	number = ft_itoa(line);
	ft_putstr_fd(number, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free(number);
	return (1);
}

void	prompt_info(t_dlist *env_list)
{
	(void)env_list;
	if (DEBUG_FLAG)
		printf("%-4.d|", status_handler(0, NULL, SH_GET));
}
