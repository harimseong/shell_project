/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 18:27:00 by gson              #+#    #+#             */
/*   Updated: 2022/06/13 01:10:14 by gson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <signal.h>
# include <sys/errno.h>
# include "dlinkedlist.h"
# include "libft.h"

int	g_exit_code;

typedef struct s_env {
	char			*key;
	char			*value;
	int				has_equal;
}	t_env;

char		**ft_split_first(const char *str, const char *delim);
void		delete_content(void *env);
int			key_compare(void *node1, void *node2);
int			env(t_dlist *envlist, int argc, char **argv);
int			cd(t_dlist *envlist, int argc, char **argv);
int			export(t_dlist *envlist, int argc, char **argv);
int			unset(t_dlist *envlist, int argc, char **argv);
int			echo(t_dlist *envlist, int argc, char **argv);
int			builtin_exit(t_dlist *envlist, int argc, char **argv);
long long	ft_atoll(char *str, int *error);
int			is_contain_special(char *str);
int			check_identifier_first(char identifier);
t_dlist		*set_envlist(char **cpenv, t_dlist *envlist);
char		**copy_env(char	**cpenv, char **envp);
t_env		*set_env(char *fullenv);
void		*copy_env_content(void *content);;
void		handle_signals_cmd(void);
void		handle_signals(void);
#endif
