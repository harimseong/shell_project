/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 13:26:19 by hseong            #+#    #+#             */
/*   Updated: 2022/06/08 05:00:57 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
/*
 * 0xf0000000 	Operator bit-mask
 * LSB = 1 		expandable operator
 * LSB = 2 		non-expandable operator
 *			 	|f000|0000|
 * |operator category|operator type|
 */
enum e_token_type
{
	TT_EMPTY = 0,
	TT_WORD = 0x01000000,
//	TT_ASSIGNMENT_WORD = 0x00000020,
	/* operators */
	TT_OPERATOR = 0x02000000,
	TT_PIPELINE = 0x02010000,		/* pipeline operators */
	TT_AND = 0x02010010,				/* '&&' */
	TT_OR = 0x02010020,				/* '||' */
	TT_REDIRECT = 0x02020000,	/* redirection operators */
	TT_LESS = 0x02020001,			/* '<' */
	TT_DLESS = 0x02020002,		/* '<<' */
	TT_GREAT = 0x02020011,		/* '>' */
	TT_DGREAT = 0x02020012,		/* '>>' */
	TT_PIPE = 0x02040000,
	TT_QUOTE_MASK = 0x04080000,
//	TT_QUOTE_START = 0x0408010,
	TT_SQUOTE = 0x04080020,
	TT_DQUOTE = 0x04080040,
	TT_ERROR = 0x80000000
};

enum e_token_handler
{
	TH_GET,
	TH_SET,
	TH_PEEK
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
	char	*word;
	int		type;
}				t_token;

typedef char	**t_token_arr;

t_token	*token_handler(int type, t_iterator *iterator);
int		check_token_type(int type, int comp);
//t_token	*make_token(char *word, int type);

#endif
