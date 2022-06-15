/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 13:26:19 by hseong            #+#    #+#             */
/*   Updated: 2022/06/15 19:53:08 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "dlinkedlist.h"

/*
 * 0xf0000000 	Operator bit-mask
 * LSB = 1 		expandable operator
 * LSB = 2 		non-expandable operator
 *			 	|f000|0000|
 * |operator category|operator type|
 */
typedef enum e_token_type
{
	TT_EMPTY = 0x00000000,
	TT_WORD = 0x01000000,
	TT_OPERATOR = 0x02000000,
	TT_PIPELINE = 0x02010000,
	TT_AND = 0x02010010,
	TT_OR = 0x02010020,
	TT_REDIRECT = 0x02020000,
	TT_LESS = 0x02020001,
	TT_DLESS = 0x02020002,
	TT_GREAT = 0x02020004,
	TT_DGREAT = 0x02020008,
	TT_PIPE = 0x02040000,
	TT_CONTROL_OP = 0x02080000,
	TT_AMPERSAND = 0x020800010,
	TT_QUOTE_MASK = 0x04000000,
	TT_SQUOTE = 0x04000020,
	TT_DQUOTE = 0x04000040,
	TT_ERROR = 0x40000000
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
