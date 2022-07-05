/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:08:40 by hseong            #+#    #+#             */
/*   Updated: 2022/06/30 21:03:07 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_RECOGNITION_H
# define TOKEN_RECOGNITION_H

# include "parser/token.h"

# define CONTINUE (0)
# define DELIMIT (1)
# define APPLIED (2)

typedef int	(*t_token_recog_func)(t_iterator *, t_token *, char target);

int		check_eoi(t_iterator *iterator, t_token *token, char target);
int		check_operator(t_iterator *iterator, t_token *token, char target);
int		check_quote(t_iterator *iterator, t_token *token, char target);
int		check_dollar(t_iterator *iterator, t_token *token, char target);
int		check_new_operator(t_iterator *iterator, t_token *token, char target);
int		check_blank(t_iterator *iterator, t_token *token, char target);
int		check_word(t_iterator *iterator, t_token *token, char target);
int		check_new_word(t_iterator *iterator, t_token *token, char target);

// helper functions
char	get_char(t_node *node);
int		get_operator_type(char target);
int		check_long_operator(char target, t_token_type *type);
char	*dlist_to_string(t_node *start, size_t len);
int		is_ifs(char c);

int		expand_word(t_iterator *iterator, int token_type);
int		expand_asterisk(t_iterator *iterator, t_node *expand_point,
		int token_type);
int		special_expansion(t_iterator *iterator, char target, int token_type);
char	*convert_str_to_quoted(char *string);
int		get_subshell_token(t_iterator *iterator);

# define TABLE_SIZE (8)

static const
	t_token_recog_func g_token_recog_tab[8]
	= {
	check_eoi,
	check_operator,
	check_quote,
	check_dollar,
	check_new_operator,
	check_blank,
	check_word,
	check_new_word
};

#endif
