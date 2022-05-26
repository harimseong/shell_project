/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:36:10 by hseong            #+#    #+#             */
/*   Updated: 2022/05/26 14:14:07 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/token.h"
#include "libft.h"

void	delimit_token(t_input_line *input_line);
{
	if (context->type == 0)
	{
		++context->token_itr;
		return ;
	}
	else
	{
		push_back(token_list, ft_strndup(context->token_begin,
			context->token_itr - context->token_begin));
		context->type = 0;
		++context->token_itr;
	}

}

void	do_nothing(t_dlist *token_list, t_token_context *context)
{
	(void)token_list;
	(void)context;
}
