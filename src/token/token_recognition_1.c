/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:36:10 by hseong            #+#    #+#             */
/*   Updated: 2022/05/11 18:16:35 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_token.h"

void	delimit_token(t_dlist *token_list, t_token_context *context)
{
	if (context->type == 0)
	{
		++context->token_start;
		return ;
	}

}

void	do_nothing(t_dlist *token_list, t_token_context *context)
{
	(void)token_list;
	(void)context;
}
