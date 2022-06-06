/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:13:36 by hseong            #+#    #+#             */
/*   Updated: 2022/06/03 18:06:15 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "parser/token.h"
#include "parser/token_recognition.h"
#include "libft.h"

t_token	*char_plus(t_iterator *iterator)
{
	return (exceptional_char(iterator));
}

t_token	*char_comma(t_iterator *iterator)
{
	return (exceptional_char(iterator));
}

t_token	*char_minus(t_iterator *iterator)
{
	return (exceptional_char(iterator));
}

t_token	*char_dot(t_iterator *iterator)
{
	return (exceptional_char(iterator));
}

t_token	*char_plus(t_iterator *iterator)
{
	return (exceptional_char(iterator));
}
