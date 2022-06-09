/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:10:42 by hseong            #+#    #+#             */
/*   Updated: 2022/06/03 15:13:30 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "parser/token.h"
#include "parser/token_recognition.h"
#include "libft.h"

t_token	*char_excl(t_iterator *iterator)
{
	return (exceptional_char(iterator));
}

t_token	*char_hash(t_iterator *iterator)
{
	return (exceptional_char(iterator));
}

t_token	*char_percent(t_iterator *iterator)
{
	return (exceptional_char(iterator));
}

t_token	*char_paren_open(t_iterator *iterator)
{
	return (exceptional_char(iterator));
}

t_token	*char_paren_close(t_iterator *iterator)
{
	return (exceptional_char(iterator));
}
