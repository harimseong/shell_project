/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 21:54:15 by hseong            #+#    #+#             */
/*   Updated: 2022/06/15 18:07:00 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "parser/token.h"

# ifndef DEBUG_FLAG
#  define DEBUG_FLAG (0)
# endif

# define REDIR_NUM_OPS (4)

enum e_redir
{
	REDIR_IN = 0,
	REDIR_OUT = 1,
	REDIR_APPEND = 2,
	REDIR_HEREDOC = 3,
	REDIR_PROCESSED = 0xff
};

enum e_command
{
	CMD_NORMAL = 0,
	CMD_HEREDOC
};

typedef struct s_redirect
{
	enum e_redir	redir_type;
	int				descriptor;
	char			*heredoc;
	char			*filename;
	t_token			*token_set[2];
}			t_redirect;

/*
 * word_list->content		= t_token
 * redirect_list->content	= t_redirect
 */
typedef struct s_command
{
	int			flag;
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

//void	set_command(t_dlist *command_list);
//void	set_redirect(t_dlist *redirect_list);
void	parser_error(t_dlist *list, t_token *token);

#endif
