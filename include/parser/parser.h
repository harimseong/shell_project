/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 21:54:15 by hseong            #+#    #+#             */
/*   Updated: 2022/06/08 22:18:02 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "parser/token.h"

# ifndef DEBUG_FLAG
#  define DEBUG_FLAG (0)
# endif

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
	t_token			*token_set[2];
}			t_redirect;

/*
 * word_list->content		= t_token
 * redirect_list->content	= t_redirect
 */
typedef struct s_command
{
	t_dlist		*word_list;
	t_dlist		*redirect_list;
}			t_command;

/*
 * command_list->content	= t_command
 */
typedef struct s_pipeline
{
	int			result;
	int			pipeline_type;
	t_dlist		*command_list;
}			t_pipeline;

//void	set_command(t_token *token, t_dlist *pipeline_list);
//void	set_arguments(t_token *token, t_dlist *pipeline_list);
//void
//set_redirection(t_token *operator, t_token *word, t_dlist *pipeline_list);
void	parser_error(t_dlist *list, t_token *token);
void	pipeline_list_delete(void *pipeline);
void	pipeline_list_print(void *pipeline);

#endif
