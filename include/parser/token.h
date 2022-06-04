/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 13:26:19 by hseong            #+#    #+#             */
/*   Updated: 2022/06/04 23:19:30 by hseong           ###   ########.fr       */
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
	TT_WORD = 0x00000010,
	TT_ASSIGNMENT_WORD = 0x00000020,
	/* operators */
	TT_OPERATOR = 0x70000000,
	TT_DOLLAR = 0x70000010,
	TT_PIPELINE = 0x70010000,		/* pipeline operators */
	TT_AND = 0x70010010,				/* '&&' */
	TT_OR = 0x70010020,				/* '||' */
	TT_REDIRECT = 0x70020000,	/* redirection operators */
	TT_LESS = 0x70020001,			/* '<' */
	TT_DLESS = 0x70020002,		/* '<<' */
	TT_GREAT = 0x70020011,		/* '>' */
	TT_DGREAT = 0x70020012,		/* '>>' */
	TT_QUOTE_MASK = 0x70040000,
	TT_SQUOTE = 0x70040010,
	TT_DQUOTE = 0x70040020,
	TT_PIPE = 0x70080000,
	TT_ERROR = 0x7fff0000
};

enum e_token_handler
{
	TH_GET,
	TH_SET,
	TH_PEEK
};

typedef struct s_iterator
{
	char	*line;
	int		start;
	int		end;
}				t_iterator;

typedef struct s_token
{
	char	*word;
	int		type;
}				t_token;

typedef char	**t_token_arr;

t_token	*token_handler(int type, t_iterator *iterator);
//t_token	*make_token(char *word, int type);

#endif
