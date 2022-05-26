/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 21:54:15 by hseong            #+#    #+#             */
/*   Updated: 2022/05/26 21:53:33 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

enum e_redir
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
};

typedef struct s_redirect
{
	enum e_redir	redir_type;
	int				descriptor;
	char			*heredoc;
}			t_redirect;

typedef struct s_command
{
	t_dlist	word_list;
	t_dlist	redirect_list;
}			t_command;

typedef struct s_pipeline
{
	int		pipeline_type;
	t_dlist	command_list;
}			t_pipeline;

void	set_command(t_token *token, t_dlist *pipeline_list);
void	parser_error(t_token *token);

#endif
