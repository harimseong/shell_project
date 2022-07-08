/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper_func.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 23:19:41 by hseong            #+#    #+#             */
/*   Updated: 2022/07/08 15:47:08 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "parser/token_recognition.h"

static const int	g_token_type_tab[128]
	= {
	/*0 nul*/TT_EMPTY,
	/*1 soh*/TT_ERROR,
	/*2 stx*/TT_ERROR,
	/*3 etx*/TT_ERROR,
	/*4 eot*/TT_ERROR,
	/*5 enq*/TT_ERROR,
	/*6 ack*/TT_ERROR,
	/*7 bel*/TT_ERROR,
	/*8 bs*/TT_ERROR,
	/*9 ht*/TT_EMPTY,
	/*10 nl*/TT_EMPTY,
	/*11 vt*/TT_EMPTY,
	/*12 np*/TT_EMPTY,
	/*13 cr*/TT_EMPTY,
	/*14 so*/TT_ERROR,
	/*15 si*/TT_ERROR,
	/*16 dle*/TT_ERROR,
	/*17 dc1*/TT_ERROR,
	/*18 dc2*/TT_ERROR,
	/*19 dc3*/TT_ERROR,
	/*20 dc4*/TT_ERROR,
	/*21 nak*/TT_ERROR,
	/*22 syn*/TT_ERROR,
	/*23 etb*/TT_ERROR,
	/*24 can*/TT_ERROR,
	/*25 em*/TT_ERROR,
	/*26 sub*/TT_ERROR,
	/*27 esc*/TT_ERROR,
	/*28 fs*/TT_ERROR,
	/*29 gs*/TT_ERROR,
	/*30 rs*/TT_ERROR,
	/*31 us*/TT_ERROR,
	/*32 sp*/TT_EMPTY,
	/*33  !*/TT_ERROR,
	/*34  "*/TT_DQUOTE,
	/*35  #*/TT_ERROR,
	/*36  $*/TT_ERROR,
	/*37  %*/TT_ERROR,
	/*38  &*/TT_AMPERSAND,
	/*39  '*/TT_SQUOTE,
	/*40  (*/TT_PAREN_OPEN,
	/*41  )*/TT_PAREN_CLOSE,
	/*42  **/TT_WORD,
	/*43  +*/TT_WORD,
	/*44  ,*/TT_WORD,
	/*45  -*/TT_WORD,
	/*46  .*/TT_WORD,
	/*47  /*/TT_WORD,
	/*48  0*/TT_WORD,
	/*49  1*/TT_WORD,
	/*50  2*/TT_WORD,
	/*51  3*/TT_WORD,
	/*52  4*/TT_WORD,
	/*53  5*/TT_WORD,
	/*54  6*/TT_WORD,
	/*55  7*/TT_WORD,
	/*56  8*/TT_WORD,
	/*57  9*/TT_WORD,
	/*58  :*/TT_WORD,
	/*59  ;*/TT_ERROR,
	/*60  <*/TT_LESS,
	/*61  =*/TT_WORD,
	/*62  >*/TT_GREAT,
	/*63  ?*/TT_WORD,
	/*64  @*/TT_WORD,
	/*65  A*/TT_WORD,
	/*66  B*/TT_WORD,
	/*67  C*/TT_WORD,
	/*68  D*/TT_WORD,
	/*69  E*/TT_WORD,
	/*70  F*/TT_WORD,
	/*71  G*/TT_WORD,
	/*72  H*/TT_WORD,
	/*73  I*/TT_WORD,
	/*74  J*/TT_WORD,
	/*75  K*/TT_WORD,
	/*76  L*/TT_WORD,
	/*77  M*/TT_WORD,
	/*78  N*/TT_WORD,
	/*79  O*/TT_WORD,
	/*80  P*/TT_WORD,
	/*81  Q*/TT_WORD,
	/*82  R*/TT_WORD,
	/*83  S*/TT_WORD,
	/*84  T*/TT_WORD,
	/*85  U*/TT_WORD,
	/*86  V*/TT_WORD,
	/*87  W*/TT_WORD,
	/*88  X*/TT_WORD,
	/*89  Y*/TT_WORD,
	/*90  Z*/TT_WORD,
	/*91  [*/TT_WORD,
	/*92  \*/TT_ERROR,
	/*93  ]*/TT_WORD,
	/*94  ^*/TT_ERROR,
	/*95  _*/TT_WORD,
	/*96  `*/TT_ERROR,
	/*97  a*/TT_WORD,
	/*98  b*/TT_WORD,
	/*99  c*/TT_WORD,
	/*100  d*/TT_WORD,
	/*101  e*/TT_WORD,
	/*102  f*/TT_WORD,
	/*103  g*/TT_WORD,
	/*104  h*/TT_WORD,
	/*105  i*/TT_WORD,
	/*106  j*/TT_WORD,
	/*107  k*/TT_WORD,
	/*108  l*/TT_WORD,
	/*109  m*/TT_WORD,
	/*110  n*/TT_WORD,
	/*111  o*/TT_WORD,
	/*112  p*/TT_WORD,
	/*113  q*/TT_WORD,
	/*114  r*/TT_WORD,
	/*115  s*/TT_WORD,
	/*116  t*/TT_WORD,
	/*117  u*/TT_WORD,
	/*118  v*/TT_WORD,
	/*119  w*/TT_WORD,
	/*120  x*/TT_WORD,
	/*121  y*/TT_WORD,
	/*122  z*/TT_WORD,
	/*123  {*/TT_WORD,
	/*124  |*/TT_PIPE,
	/*125  }*/TT_WORD,
	/*126  ~*/TT_WORD,
	/*127 del*/TT_ERROR
};

int	check_token_type(t_token_type type, t_token_type comp)
{
	return ((type & (!!comp * comp + !comp * 0x7fffffff)) == comp);
}

int	check_long_operator(char target, t_token_type *type)
{
	if (!((check_token_type(*type, TT_LESS) && target == '<')
			|| (check_token_type(*type, TT_GREAT) && target == '>')
			|| (check_token_type(*type, TT_PIPE) && target == '|')
			|| (check_token_type(*type, TT_AMPERSAND) && target == '&')))
		return (DELIMIT);
	*type = TT_DLESS * (target == '<') + TT_DGREAT * (target == '>')
		+ TT_OR * (target == '|') + TT_AND * (target == '&');
	return (APPLIED);
}

char	get_char(t_node *node)
{
	if (node == NULL)
		return ('\0');
	return (*(char *)node->content);
}

char	*dlist_to_string(t_node *node, size_t len)
{
	char	*word;
	size_t	idx;

	word = malloc(len + 1);
	word[len] = 0;
	idx = 0;
	while (node && idx < len)
	{
		word[idx] = get_char(node);
		++idx;
		node = node->next;
	}
	return (word);
}

int	get_operator_type(char target)
{
	return (g_token_type_tab[(int)target]);
}
