/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 21:54:15 by hseong            #+#    #+#             */
/*   Updated: 2022/05/09 15:31:34 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TOKEN_H
# define MINISHELL_TOKEN_H

# include "dlinkedlist.h"

enum e_token_type
{
	TOKEN_WORD = 1,
	TOKEN_ASSIGNMENT_WORD,
	TOKEN_NEWLINE,
	TOKEN_IO_NUMBER,
	TOKEN_AND_IF,	/* '&&' */
	TOKEN_OR_IF,	/* '||' */
	TOKEN_DLESS,	/* '<<' */
	TOKEN_DGREAT	/* '>>' */
};

typedef struct s_token_context
{
	int			type;
	t_uint64	start_idx;
}				t_token_context;

typedef void	(*t_token_func)(void *, t_token_context *);
typedef char	**t_token_arr;

void	delimit_token(void *arg, t_token_context *context);
void	do_nothing(void *arg, t_token_context *context);
void	char_excl(void *arg, t_token_context *context);
void	char_double_quote(void *arg, t_token_context *context);
void	char_hash(void *arg, t_token_context *context);
void	char_dolor(void *arg, t_token_context *context);
void	char_percent(void *arg, t_token_context *context);
void	char_ampersand(void *arg, t_token_context *context);
void	char_single_quote(void *arg, t_token_context *context);
void	char_paren_open(void *arg, t_token_context *context);
void	char_paren_close(void *arg, t_token_context *context);
void	char_asterisk(void *arg, t_token_context *context);
void	char_plus(void *arg, t_token_context *context);
void	char_comma(void *arg, t_token_context *context);
void	char_minus(void *arg, t_token_context *context);
void	char_dot(void *arg, t_token_context *context);
void	char_slash(void *arg, t_token_context *context);
void	char_num(void *arg, t_token_context *context);
void	char_alphabet(void *arg, t_token_context *context);
void	char_colon(void *arg, t_token_context *context);
void	char_semicolon(void *arg, t_token_context *context);
void	char_less(void *arg, t_token_context *context);
void	char_equal(void *arg, t_token_context *context);
void	char_greater(void *arg, t_token_context *context);
void	char_question(void *arg, t_token_context *context);
void	char_at(void *arg, t_token_context *context);
void	char_bracket_open(void *arg, t_token_context *context);
void	char_backslash(void *arg, t_token_context *context);
void	char_bracket_close(void *arg, t_token_context *context);
void	char_caret(void *arg, t_token_context *context);
void	char_underbar(void *arg, t_token_context *context);
void	char_backtick(void *arg, t_token_context *context);
void	char_braces_open(void *arg, t_token_context *context);
void	char_vertical_bar(void *arg, t_token_context *context);
void	char_braces_close(void *arg, t_token_context *context);
void	char_tilde(void *arg, t_token_context *context);

static const
	t_token_func	g_token_char_tab[128] = {
	/*0 nul*/delimit_token,
	/*1 soh*/do_nothing,
	/*2 stx*/do_nothing,
	/*3 etx*/do_nothing,
	/*4 eot*/do_nothing,
	/*5 enq*/do_nothing,
	/*6 ack*/do_nothing,
	/*7 bel*/do_nothing,
	/*8 bs*/do_nothing,
	/*9 ht*/delimit_token,
	/*10 nl*/delimit_token,
	/*11 vt*/delimit_token,
	/*12 np*/delimit_token,
	/*13 cr*/delimit_token,
	/*14 so*/do_nothing,
	/*15 si*/do_nothing,
	/*16 dle*/do_nothing,
	/*17 dc1*/do_nothing,
	/*18 dc2*/do_nothing,
	/*19 dc3*/do_nothing,
	/*20 dc4*/do_nothing,
	/*21 nak*/do_nothing,
	/*22 syn*/do_nothing,
	/*23 etb*/do_nothing,
	/*24 can*/do_nothing,
	/*25 em*/do_nothing,
	/*26 sub*/do_nothing,
	/*27 esc*/do_nothing,
	/*28 fs*/do_nothing,
	/*29 gs*/do_nothing,
	/*30 rs*/do_nothing,
	/*31 us*/do_nothing,
	/*32 sp*/delimit_token,
	/*33  !*/char_excl,
	/*34  "*/char_double_quote,
	/*35  #*/char_hash,
	/*36  $*/char_dolor,
	/*37  %*/char_percent,
	/*38  &*/char_ampersand,
	/*39  '*/char_single_quote,
	/*40  (*/char_paren_open,
	/*41  )*/char_paren_close,
	/*42  **/char_asterisk,
	/*43  +*/char_plus,
	/*44  ,*/char_comma,
	/*45  -*/char_minus,
	/*46  .*/char_dot,
	/*47 / */char_slash,
	/*48  0*/char_num,
	/*49  1*/char_num,
	/*50  2*/char_num,
	/*51  3*/char_num,
	/*52  4*/char_num,
	/*53  5*/char_num,
	/*54  6*/char_num,
	/*55  7*/char_num,
	/*56  8*/char_num,
	/*57  9*/char_num,
	/*58  :*/char_colon,
	/*59  ;*/char_semicolon,
	/*60  <*/char_less,
	/*61  =*/char_equal,
	/*62  >*/char_greater,
	/*63  ?*/char_question,
	/*64  @*/char_at,
	/*65  A*/char_alphabet,
	/*66  B*/char_alphabet,
	/*67  C*/char_alphabet,
	/*68  D*/char_alphabet,
	/*69  E*/char_alphabet,
	/*70  F*/char_alphabet,
	/*71  G*/char_alphabet,
	/*72  H*/char_alphabet,
	/*73  I*/char_alphabet,
	/*74  J*/char_alphabet,
	/*75  K*/char_alphabet,
	/*76  L*/char_alphabet,
	/*77  M*/char_alphabet,
	/*78  N*/char_alphabet,
	/*79  O*/char_alphabet,
	/*80  P*/char_alphabet,
	/*81  Q*/char_alphabet,
	/*82  R*/char_alphabet,
	/*83  S*/char_alphabet,
	/*84  T*/char_alphabet,
	/*85  U*/char_alphabet,
	/*86  V*/char_alphabet,
	/*87  W*/char_alphabet,
	/*88  X*/char_alphabet,
	/*89  Y*/char_alphabet,
	/*90  Z*/char_alphabet,
	/*91  [*/char_bracket_open,
	/*92  \*/char_backslash,
	/*93  ]*/char_bracket_close,
	/*94  ^*/char_caret,
	/*95  _*/char_underbar,
	/*96  `*/char_backtick,
	/*97  a*/char_alphabet,
	/*98  b*/char_alphabet,
	/*99  c*/char_alphabet,
	/*100  d*/char_alphabet,
	/*101  e*/char_alphabet,
	/*102  f*/char_alphabet,
	/*103  g*/char_alphabet,
	/*104  h*/char_alphabet,
	/*105  i*/char_alphabet,
	/*106  j*/char_alphabet,
	/*107  k*/char_alphabet,
	/*108  l*/char_alphabet,
	/*109  m*/char_alphabet,
	/*110  n*/char_alphabet,
	/*111  o*/char_alphabet,
	/*112  p*/char_alphabet,
	/*113  q*/char_alphabet,
	/*114  r*/char_alphabet,
	/*115  s*/char_alphabet,
	/*116  t*/char_alphabet,
	/*117  u*/char_alphabet,
	/*118  v*/char_alphabet,
	/*119  w*/char_alphabet,
	/*120  x*/char_alphabet,
	/*121  y*/char_alphabet,
	/*122  z*/char_alphabet,
	/*123  {*/char_braces_open,
	/*124  |*/char_vertical_bar,
	/*125  }*/char_braces_close,
	/*126  ~*/char_tilde,
	/*127 del*/do_nothing
};

#endif
