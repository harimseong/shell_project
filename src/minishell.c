/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:00:17 by hseong            #+#    #+#             */
/*   Updated: 2022/05/20 21:33:12 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "dlinkedlist.h"
#include "libft.h"
#include <readline/readline.h>
#include <unistd.h>

static const char	*g_prompt = "$> ";

int	main(int argc, char *argv[], char *envp[])
{
	t_dlist		*token_list;

	token_list = (void *)1;
	(void)argc;
	(void)argv;
	(void)envp;
	while (token_list != NULL)
	{
		minishell_parse_token(readline(g_prompt));
		//delete_dlist(token_list, delete_item);
	}
	return (0);
}

void	print_item(t_token *token)
{
	ft_putstr_fd(token->token, 1);
	write(1, " ", 1);
}
