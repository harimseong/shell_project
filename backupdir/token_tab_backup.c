/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tab_backup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 23:18:07 by hseong            #+#    #+#             */
/*   Updated: 2022/06/09 15:56:20 by gson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static const
	t_token_func g_token_tab[128] = {
	/*0 nul*/char_delimiter,
	/*1 soh*/exceptional_char,
	/*2 stx*/exceptional_char,
	/*3 etx*/exceptional_char,
	/*4 eot*/exceptional_char,
	/*5 enq*/exceptional_char,
	/*6 ack*/exceptional_char,
	/*7 bel*/exceptional_char,
	/*8 bs*/exceptional_char,
	/*9 ht*/char_delimiter,
	/*10 nl*/char_delimiter,
	/*11 vt*/char_delimiter,
	/*12 np*/char_delimiter,
	/*13 cr*/char_delimiter,
	/*14 so*/exceptional_char,
	/*15 si*/exceptional_char,
	/*16 dle*/exceptional_char,
	/*17 dc1*/exceptional_char,
	/*18 dc2*/exceptional_char,
	/*19 dc3*/exceptional_char,
	/*20 dc4*/exceptional_char,
	/*21 nak*/exceptional_char,
	/*22 syn*/exceptional_char,
	/*23 etb*/exceptional_char,
	/*24 can*/exceptional_char,
	/*25 em*/exceptional_char,
	/*26 sub*/exceptional_char,
	/*27 esc*/exceptional_char,
	/*28 fs*/exceptional_char,
	/*29 gs*/exceptional_char,
	/*30 rs*/exceptional_char,
	/*31 us*/exceptional_char,
	/*32 sp*/char_delimiter,
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
	/*127 del*/exceptional_char
};
