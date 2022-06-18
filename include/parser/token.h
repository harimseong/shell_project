/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 13:26:19 by hseong            #+#    #+#             */
/*   Updated: 2022/06/18 16:38:51 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "dlinkedlist.h"

typedef enum e_token_type
{
	TT_EMPTY =			0x00000000,
	TT_WORD =			0x01000000,
	TT_OPERATOR =		0x02000000,
	TT_PIPELINE =		0x02010000,
	TT_AND =			0x02010001,
	TT_OR =				0x02010002,
	TT_REDIRECT =		0x02020000,
	TT_LESS =			0x02020001,
	TT_DLESS =			0x02020002,
	TT_GREAT =			0x02020004,
	TT_DGREAT =			0x02020008,
	TT_PIPE =			0x02040000,
	TT_CONTROL_OP =		0x02080000,
	TT_AMPERSAND =		0x02080001,
	TT_QUOTE_MASK =		0x04000000,
	TT_SQUOTE =			0x04000001,
	TT_DQUOTE =			0x04000002,
	TT_DOLLAR =			0x08000000,
	TT_REDIR_ERROR =	0x20000000,
	TT_ERROR =			0x40000000
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
	int		len;
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
