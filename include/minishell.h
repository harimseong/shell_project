/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:59:46 by hseong            #+#    #+#             */
/*   Updated: 2022/06/19 19:30:38 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>

# include "parser/token.h"
# include "sys/errno.h"

enum e_signal_handler
{
	SH_START = 0,
	SH_SET,
	SH_GET
};

t_dlist	*parser(const char *line, t_dlist *env_list);
void	read_pipeline(t_dlist *pipeline_list, t_dlist *env_list);
int		builtin_exit(t_dlist *env_list, int argc, char **argv);
int		builtin_print_exit(t_dlist *env_list, int argc, char **argv);
int		builtin_set_exit(t_dlist *env_list, int status, int argc, char **argv);

int		status_handler(int status, t_dlist *new_env_list, int type);

// delete parsed data
void	delete_pipeline_content(void *pipeline_arg);
void	delete_command_content(void *command_arg);
void	delete_word_content(void *token_arg);
void	delete_redirect_content(void *redirect_arg);
void	delete_env_content(void *env_arg);
void	delete_no_content(void *arg);
void	delete_item(t_token **token);

void	pipeline_content_print(void *pipeline);
void	print_item(t_token *token);

void	minishell_errormsg(const char *s1, const char *s2, const char *s3);
int		minishell_assert(int is_true, const char *file, int line);

#endif
