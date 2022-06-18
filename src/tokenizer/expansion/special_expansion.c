/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:55:06 by hseong            #+#    #+#             */
/*   Updated: 2022/06/18 21:44:30 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cmd.h"
#include "libft.h"

#include "minishell.h"
#include "execute.h"
#include "constants.h"
#include "parser/token_recognition.h"

typedef int		(*t_expand_func)(t_iterator *, t_node *, int);

extern t_dlist	*g_env_list;

int
expand_asterisk(t_iterator *iterator, t_node *expand_point, int token_type);

static int
expand_question(t_iterator *iterator, t_node *expand_point, int token_type);
static int
expand_tilde(t_iterator *iterator, t_node *expand_point, int token_type);
static int
expand_number(t_iterator *iterator, t_node *expand_point, int token_type);

static const
	t_expand_func g_special_expansion_tab[128]
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
	/*38  &*/0,
	/*39  '*/0,
	/*40  (*/0,
	/*41  )*/0,
	/*42  **/expand_asterisk,
	/*43  +*/0,
	/*44  ,*/0,
	/*45  -*/0,
	/*46  .*/0,
	/*47  /*/0,
	/*48  0*/expand_number,
	/*49  1*/expand_number,
	/*50  2*/expand_number,
	/*51  3*/expand_number,
	/*52  4*/expand_number,
	/*53  5*/expand_number,
	/*54  6*/expand_number,
	/*55  7*/expand_number,
	/*56  8*/expand_number,
	/*57  9*/expand_number,
	/*58  :*/0,
	/*59  ;*/0,
	/*60  <*/0,
	/*61  =*/0,
	/*62  >*/0,
	/*63  ?*/expand_question,
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
	/*124  |*/0,
	/*125  }*/0,
	/*126  ~*/expand_tilde,
	/*127 del*/0
};

int	special_expansion(t_iterator *iterator, char target, int token_type)
{
	t_node	*expand_point;
	int		status;

	expand_point = iterator->line->cur->next;
	if (check_token_type(token_type, TT_DOLLAR))
		expand_point = expand_point->next;
	status = g_special_expansion_tab[(int)target](iterator, expand_point,
			token_type);
	minishell_assert(status == 0, __FILE__, __LINE__);
	iterator->line->cur = iterator->line->cur->next;
	erase_at(iterator->line, iterator->line->cur->prev, free);
	return (0);
}

int	expand_question(t_iterator *iterator, t_node *expand_point, int token_type)
{
	char	*status_str;
	size_t	idx;

	(void)token_type;
	status_str = *find_question(g_env_list);
	idx = 0;
	erase_at(iterator->line, expand_point->prev, free);
	while (status_str[idx])
	{
		insert_at(iterator->line, expand_point,
			ft_strndup(status_str + idx++, 1));
	}
	return (0);
}

int	expand_tilde(t_iterator *iterator, t_node *expand_point, int token_type)
{
	char	*home_dir;
	size_t	idx;

	home_dir = find_env_by_key(g_env_list, "HOME");
	if (check_token_type(token_type, TT_QUOTE_MASK) || home_dir == NULL)
		return (0);
	idx = 0;
	while (home_dir[idx])
	{
		insert_at(iterator->line, expand_point,
			ft_strndup(home_dir + idx++, 1));
	}
	return (0);
}

int	expand_number(t_iterator *iterator, t_node *expand_point, int token_type)
{
	(void)token_type;
	erase_at(iterator->line, expand_point->prev, free);
	return (0);
}
