/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 13:26:19 by hseong            #+#    #+#             */
/*   Updated: 2022/06/03 21:27:03 by hseong           ###   ########.fr       */
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
	TT_WORD,
	TT_ASSIGNMENT_WORD,
	/* operators */
	TT_OPERATOR = 0x70000000,
	TT_PIPELINE = 0x70010000,		/* pipeline operators */
	TT_AND = 0x70010004,				/* '&&' */
	TT_OR = 0x70010008,				/* '||' */
	TT_REDIRECT = 0x70020000,	/* redirection operators */
	TT_LESS = 0x70020001,			/* '<' */
	TT_DLESS = 0x70020002,		/* '<<' */
	TT_GREAT = 0x70020011,		/* '>' */
	TT_DGREAT = 0x70020012,		/* '>>' */
	TT_QUOTE_MASK = 0x70040000,
	TT_SQUOTE = 0x70040004,
	TT_DQUOTE = 0x70040008,
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

/* token recognition functions */
int		char_delimiter(t_iterator *iterator, t_token *token);
int		exceptional_char(t_iterator *iterator, t_token *token);
int		char_excl(t_iterator *iterator, t_token *token);
int		char_double_quote(t_iterator *iterator, t_token *token);
int		char_hash(t_iterator *iterator, t_token *token);
int		char_dolor(t_iterator *iterator, t_token *token);
int		char_percent(t_iterator *iterator, t_token *token);
int		char_ampersand(t_iterator *iterator, t_token *token);
int		char_single_quote(t_iterator *iterator, t_token *token);
int		char_paren_open(t_iterator *iterator, t_token *token);
int		char_paren_close(t_iterator *iterator, t_token *token);
int		char_asterisk(t_iterator *iterator, t_token *token);
int		char_plus(t_iterator *iterator, t_token *token);
int		char_comma(t_iterator *iterator, t_token *token);
int		char_minus(t_iterator *iterator, t_token *token);
int		char_dot(t_iterator *iterator, t_token *token);
int		char_slash(t_iterator *iterator, t_token *token);
int		char_num(t_iterator *iterator, t_token *token);
int		char_alphabet(t_iterator *iterator, t_token *token);
int		char_colon(t_iterator *iterator, t_token *token);
int		char_semicolon(t_iterator *iterator, t_token *token);
int		char_less(t_iterator *iterator, t_token *token);
int		char_equal(t_iterator *iterator, t_token *token);
int		char_greater(t_iterator *iterator, t_token *token);
int		char_question(t_iterator *iterator, t_token *token);
int		char_at(t_iterator *iterator, t_token *token);
int		char_bracket_open(t_iterator *iterator, t_token *token);
int		char_backslash(t_iterator *iterator, t_token *token);
int		char_bracket_close(t_iterator *iterator, t_token *token);
int		char_caret(t_iterator *iterator, t_token *token);
int		char_underbar(t_iterator *iterator, t_token *token);
int		char_backtick(t_iterator *iterator, t_token *token);
int		char_braces_open(t_iterator *iterator, t_token *token);
int		char_vertical_bar(t_iterator *iterator, t_token *token);
int		char_braces_close(t_iterator *iterator, t_token *token);
int		char_tilde(t_iterator *iterator, t_token *token);

#endif
