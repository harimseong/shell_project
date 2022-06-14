/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 22:31:10 by hseong            #+#    #+#             */
/*   Updated: 2022/06/13 20:53:06 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "parser/parser.h"

int		redirect_in(t_redirect *redirect, int std_fd_set[2]);
int		redirect_out(t_redirect *redirect, int std_fd_set[2]);
int		redirect_append(t_redirect *redirect, int std_fd_set[2]);
int		redirect_heredoc(t_redirect *redirect, int std_fd_set[2]);

void	*get_word_from_token(void *content);
void	*env_to_str(void *content);
void	*get_key_from_env(void* content);
char	*get_value_from_env(t_dlist *env_list, const char *key);
void	free_path_arr(char **path_arr);

#endif
