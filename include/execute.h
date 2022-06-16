/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 22:31:10 by hseong            #+#    #+#             */
/*   Updated: 2022/06/16 15:18:08 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "parser/parser.h"

int		execve_wrapper(const char *filename, char **argv, char **envp,
	char **path_arr);

int		redirect_in(t_redirect *redirect);
int		redirect_out(t_redirect *redirect);
int		redirect_append(t_redirect *redirect);
int		redirect_heredoc(t_redirect *redirect);

void	*get_word_from_token(void *content);
void	*env_to_str(void *content);
void	*get_key_from_env(void *content);
char	*get_value_from_env(t_dlist *env_list, const char *key);
void	free_str_arr(char **arr);

int		is_ifs(char c);

#endif
