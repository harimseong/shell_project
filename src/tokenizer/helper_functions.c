/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 23:19:41 by hseong            #+#    #+#             */
/*   Updated: 2022/06/09 16:34:40 by gson             ###   ########.fr       */
=======
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 23:19:41 by hseong            #+#    #+#             */
/*   Updated: 2022/06/08 23:19:44 by hseong           ###   ########.fr       */
>>>>>>> upstream/master
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser/token_recognition.h"

static const int	g_token_type_tab[128]
	= {
/*0 nul*/0,
/*1 soh*/0,
/*2 stx*/0,
/*3 etx*/0,
/*4 eot*/0,
/*5 enq*/0,
/*6 ack*/0,
/*7 bel*/0,
/*8 bs*/0,
/*9 ht*/0,
/*10 nl*/0,
/*11 vt*/0,
/*12 np*/0,
/*13 cr*/0,
/*14 so*/0,
/*15 si*/0,
/*16 dle*/0,
/*17 dc1*/0,
/*18 dc2*/0,
/*19 dc3*/0,
/*20 dc4*/0,
/*21 nak*/0,
/*22 syn*/0,
/*23 etb*/0,
/*24 can*/0,
/*25 em*/0,
/*26 sub*/0,
/*27 esc*/0,
/*28 fs*/0,
/*29 gs*/0,
/*30 rs*/0,
/*31 us*/0,
/*32 sp*/0,
/*33  !*/0,
/*34  "*/0,
/*35  #*/0,
/*36  $*/0,
/*37  %*/0,
/*38  &*/TT_AMPERSAND,
/*39  '*/0,
/*40  (*/0,
/*41  )*/0,
/*42  **/0,
/*43  +*/0,
/*44  ,*/0,
/*45  -*/0,
/*46  .*/0,
/*47  /*/0,
/*48  0*/0,
/*49  1*/0,
/*50  2*/0,
/*51  3*/0,
/*52  4*/0,
/*53  5*/0,
/*54  6*/0,
/*55  7*/0,
/*56  8*/0,
/*57  9*/0,
/*58  :*/0,
/*59  ;*/0,
/*60  <*/TT_LESS,
/*61  =*/0,
/*62  >*/TT_GREAT,
/*63  ?*/0,
/*64  @*/0,
/*65  A*/0,
/*66  B*/0,
/*67  C*/0,
/*68  D*/0,
/*69  E*/0,
/*70  F*/0,
/*71  G*/0,
/*72  H*/0,
/*73  I*/0,
/*74  J*/0,
/*75  K*/0,
/*76  L*/0,
/*77  M*/0,
/*78  N*/0,
/*79  O*/0,
/*80  P*/0,
/*81  Q*/0,
/*82  R*/0,
/*83  S*/0,
/*84  T*/0,
/*85  U*/0,
/*86  V*/0,
/*87  W*/0,
/*88  X*/0,
/*89  Y*/0,
/*90  Z*/0,
/*91  [*/0,
/*92  \*/0,
/*93  ]*/0,
/*94  ^*/0,
/*95  _*/0,
/*96  `*/0,
/*97  a*/0,
/*98  b*/0,
/*99  c*/0,
/*100  d*/0,
/*101  e*/0,
/*102  f*/0,
/*103  g*/0,
/*104  h*/0,
/*105  i*/0,
/*106  j*/0,
/*107  k*/0,
/*108  l*/0,
/*109  m*/0,
/*110  n*/0,
/*111  o*/0,
/*112  p*/0,
/*113  q*/0,
/*114  r*/0,
/*115  s*/0,
/*116  t*/0,
/*117  u*/0,
/*118  v*/0,
/*119  w*/0,
/*120  x*/0,
/*121  y*/0,
/*122  z*/0,
/*123  {*/0,
/*124  |*/TT_PIPE,
/*125  }*/0,
/*126  ~*/0,
/*127 del*/0
};

int	check_token_type(int type, int comp)
{
	return ((type & comp) == comp);
}

int	check_long_operator(char target, int *type)
{
	if (!(((*type == TT_LESS) && target == '<')
<<<<<<< HEAD
			|| ((*type == TT_GREAT) && target == '>')
			|| ((*type == TT_PIPE) && target == '|')
			|| ((*type == TT_AMPERSAND) && target == '&')))
=======
		|| ((*type == TT_GREAT) && target == '>')
		|| ((*type == TT_PIPE) && target == '|')
		|| ((*type == TT_AMPERSAND) && target == '&')))
>>>>>>> upstream/master
		return (DELIMIT);
	*type = g_token_type_tab[(int)target];
	if (target == '<')
		*type = TT_DLESS;
	else if (target == '>')
		*type = TT_DGREAT;
	else if (target == '|')
		*type = TT_OR;
	else if (target == '&')
		*type = TT_AND;
	return (APPLIED);
}

char	get_char(t_node *node)
{
	if (node == NULL)
		return ('\0');
	return (*(char *)node->content);
}

char	*convert_list(t_node *node, size_t len)
{
	char	*word;
	size_t	idx;

	word = malloc(len + 1);
	word[len] = 0;
//	if (word == NULL)
//		return (NULL);
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

