/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_initialize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 21:31:07 by hseong            #+#    #+#             */
/*   Updated: 2022/06/09 23:19:20 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*minishell_initialize(int argc, char **argv)
{
	char	*prompt;

	(void)argc;
	(void)argv;
	prompt = "$> ";
	return (prompt);
}
