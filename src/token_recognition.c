/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:02:57 by hseong            #+#    #+#             */
/*   Updated: 2022/05/09 15:31:04 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_type.h"
#include "minishell_token.h"
#include "dlinkedlist.h"

int	token_recognition(char *cmd_line, t_dlist *token_list)
{
	t_token_context	context;

	context = (t_token_context){0, };
	while (cmd_line)
	{

	}
}
