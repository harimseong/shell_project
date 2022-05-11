/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:59:46 by hseong            #+#    #+#             */
/*   Updated: 2022/05/11 15:16:01 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "minishell_type.h"
#include "minishell_const.h"
#include "minishell_token.h"

void		minishell_get_cmdline(void);
void		minishell_analyze_token(t_dlist *list);
void		minishell_free_token(t_token_arr *token_arr_ptr);
t_dlist		*minishell_parse_token(char *cmd_line);

char	**ft_split(const char *str, const char *delim);

#endif
