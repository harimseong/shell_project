/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 13:26:19 by hseong            #+#    #+#             */
/*   Updated: 2022/05/26 21:34:13 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

#include "types.h"

enum e_token_type
{
	WORD = 1,
	ASSIGNMENT_WORD,
	AND_IF,	/* '&&' */
	OR_IF,	/* '||' */
	DLESS,	/* '<<' */
	DGREAT	/* '>>' */
};

enum e_token_handler
{
	TOKEN_PEEK,
	TOKEN_GET
};

typedef struct s_iterator
{
	char	*line;
	int		pos;
}				t_iterator;

typedef struct s_token
{
	int		type;
	char	*word;
}				t_token;

typedef t_token	*(*t_token_func)(t_iterator *);
typedef char	**t_token_arr;

t_token	*token_handler(t_iterator *iterator, int num);

/* token recognition functions */
t_token	*delimit_token(t_iterator *iterator);
t_token	*do_nothing(t_iterator *iterator);
t_token	*char_excl(t_iterator *iterator);
t_token	*char_double_quote(t_iterator *iterator);
t_token	*char_hash(t_iterator *iterator);
t_token	*char_dolor(t_iterator *iterator);
t_token	*char_percent(t_iterator *iterator);
t_token	*char_ampersand(t_iterator *iterator);
t_token	*char_single_quote(t_iterator *iterator);
t_token	*char_paren_open(t_iterator *iterator);
t_token	*char_paren_close(t_iterator *iterator);
t_token	*char_asterisk(t_iterator *iterator);
t_token	*char_plus(t_iterator *iterator);
t_token	*char_comma(t_iterator *iterator);
t_token	*char_minus(t_iterator *iterator);
t_token	*char_dot(t_iterator *iterator);
t_token	*char_slash(t_iterator *iterator);
t_token	*char_num(t_iterator *iterator);
t_token	*char_alphabet(t_iterator *iterator);
t_token	*char_colon(t_iterator *iterator);
t_token	*char_semicolon(t_iterator *iterator);
t_token	*char_less(t_iterator *iterator);
t_token	*char_equal(t_iterator *iterator);
t_token	*char_greater(t_iterator *iterator);
t_token	*char_question(t_iterator *iterator);
t_token	*char_at(t_iterator *iterator);
t_token	*char_bracket_open(t_iterator *iterator);
t_token	*char_backslash(t_iterator *iterator);
t_token	*char_bracket_close(t_iterator *iterator);
t_token	*char_caret(t_iterator *iterator);
t_token	*char_underbar(t_iterator *iterator);
t_token	*char_backtick(t_iterator *iterator);
t_token	*char_braces_open(t_iterator *iterator);
t_token	*char_vertical_bar(t_iterator *iterator);
t_token	*char_braces_close(t_iterator *iterator);
t_token	*char_tilde(t_iterator *iterator);

#endif
