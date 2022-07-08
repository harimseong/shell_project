/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 13:26:19 by hseong            #+#    #+#             */
/*   Updated: 2022/07/08 16:40:34 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "dlinkedlist.h"

typedef enum e_token_type
{
	TT_EMPTY =			0x00000000,
	TT_WORD =			0x00010000,

	TT_OPERATOR =		0x00020000,
	TT_PIPELINE =		0x00020100,
	TT_AND =			0x00020101,
	TT_OR =				0x00020102,

	TT_REDIRECT =		0x00020200,
	TT_LESS =			0x00020201,
	TT_DLESS =			0x00020202,
	TT_GREAT =			0x00020204,
	TT_DGREAT =			0x00020208,

	TT_PIPE =			0x00020400,
	TT_CONTROL_OP =		0x00020800,
	TT_AMPERSAND =		0x00020801,

	TT_PARENTHESIS =	0x00021000,
	TT_PAREN_OPEN =		0x00021001,
	TT_PAREN_CLOSE =	0x00021002,

	TT_QUOTE_MASK =		0x00040000,
	TT_SQUOTE =			0x00040001,
	TT_DQUOTE =			0x00040002,

	TT_DOLLAR =			0x00080000,
	TT_ASTERISK =		0x00100000,

	TT_REDIR_ERROR =	0x20000000,
	TT_ERROR =			0x40000000,
	TT_EOF_ERROR =		0x40000100,
	TT_SQUOTE_ERROR =	0x40000101,
	TT_DQUOTE_ERROR =	0x40000102
}	t_token_type;

enum e_token_handler
{
	TH_GET = 1,
	TH_SET,
	TH_PEEK,
	TH_END
};

typedef struct s_iterator
{
	t_node	*record;
	t_dlist	*line;
	t_dlist	*env_list;
}				t_iterator;

typedef struct s_token
{
	char			*word;
	t_token_type	type;
}				t_token;

typedef char	**t_token_arr;

t_token	*token_handler(int type, t_iterator *iterator);
int		check_token_type(t_token_type type, t_token_type comp);
int		recog_character(t_iterator *iterator, t_token *token);

#endif
