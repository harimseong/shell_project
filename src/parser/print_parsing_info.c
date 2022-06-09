/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parsing_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:57:22 by hseong            #+#    #+#             */
/*   Updated: 2022/06/09 16:34:12 by gson             ###   ########.fr       */
=======
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:57:22 by hseong            #+#    #+#             */
/*   Updated: 2022/06/07 13:16:25 by hseong           ###   ########.fr       */
>>>>>>> upstream/master
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "dlinkedlist.h"
#include "constants.h"
#include "parser/token.h"
#include "parser/parser.h"

static void	command_list_print(void *command);
<<<<<<< HEAD
static void	word_list_print(void *word);
static void	redirect_list_print(void *redirect);
=======
static void word_list_print(void *word);
static void redirect_list_print(void *redirect);
>>>>>>> upstream/master

void	pipeline_list_print(void *pipeline)
{
	if (pipeline == NULL)
		return ;
	printf("pipeline\n{\n");
<<<<<<< HEAD
	dlist_print_forward(((t_pipeline *)pipeline)->command_list,
		command_list_print);
=======
	dlist_print_forward(((t_pipeline *)pipeline)->command_list, command_list_print);
>>>>>>> upstream/master
	printf("}\n");
}

void	command_list_print(void *command)
{
	if (command == NULL)
		return ;
	printf("\tcommand\n");
	printf("\t{\n\t\tword_list\n");
	printf("\t\t{\n");
	dlist_print_forward(((t_command *)command)->word_list, word_list_print);
	printf("\t\t}\n");
	printf("\t\n\t\tredirect_list\n");
	printf("\t\t{\n");
	dlist_print_forward(((t_command *)command)->redirect_list,
		redirect_list_print);
	printf("\t\t}\n");
	printf("\t}\n");
}

<<<<<<< HEAD
void	word_list_print(void *word)
=======
void word_list_print(void *word)
>>>>>>> upstream/master
{
	if (word == NULL)
		return ;
	printf("\t\t\t{\n\t\t\t\ttoken word = \"%s\"\n", ((t_token *)word)->word);
	printf("\t\t\t\ttoken type = 0x%x\n\t\t\t}\n", ((t_token *)word)->type);
}

<<<<<<< HEAD
void	redirect_list_print(void *redirect_arg)
=======
void redirect_list_print(void *redirect_arg)
>>>>>>> upstream/master
{
	t_redirect	*redirect;

	redirect = redirect_arg;
	if (redirect == NULL)
		return ;
	printf("\t\t\t{\n\t\t\t\tredirection type = %d\n",
		(redirect->redir_type));
	if (redirect->heredoc != NULL)
		printf("\t\t\t\theredoc = \"%s\"\n\t\t\t}\n", redirect->heredoc);
	else
	{
		printf("\t\t\t\tfd = %d\n", redirect->descriptor);
		printf("\t\t\t\tfilename = \"%s\"\n\t\t\t}\n", redirect->token_set[1]->word);
	}
}
