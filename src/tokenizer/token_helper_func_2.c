/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper_func_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 15:43:56 by hseong            #+#    #+#             */
/*   Updated: 2022/07/08 15:48:14 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/token_recognition.h"

void	remove_mask(t_token_type *type, int mask)
{
	*type &= (0x7fffffff ^ mask);
}
