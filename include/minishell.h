/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:59:46 by hseong            #+#    #+#             */
/*   Updated: 2022/06/10 20:43:47 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "types.h"
# include "parser/token.h"

t_dlist	*parser(const char *line, t_dlist *env_list);
void	read_pipeline(t_dlist *pipeline_list, t_dlist *env_list);

void	delete_pipeline_content(void *pipeline_arg);
void	delete_command_content(void *command_arg);
void	delete_word_content(void *token_arg);
void	delete_redirect_content(void *redirect_arg);
void	delete_env_content(void *env_arg);

void	pipeline_content_print(void *pipeline);
void	print_item(t_token *token);
void	delete_item(t_token **token);

#endif
