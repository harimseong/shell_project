/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parsing_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:57:22 by hseong            #+#    #+#             */
/*   Updated: 2022/06/06 16:20:57 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "dlinkedlist.h"
#include "constants.h"
#include "parser/token.h"
#include "parser/parser.h"

static void	command_list_print(void *command);
static void word_list_print(void *word);

void	pipeline_list_print(void *pipeline)
{
	if (pipeline == NULL)
		return ;
	printf("pipeline\n");
	dlist_print_forward(((t_pipeline *)pipeline)->command_list, command_list_print);
}

void	command_list_print(void *command)
{
	if (command == NULL)
		return ;
	printf("{\n	command\n");
	dlist_print_forward(((t_command *)command)->word_list, word_list_print);
	printf("}\n");
}

void word_list_print(void *word)
{
	if (word == NULL)
		return ;
	printf("\t{\n		token word = %s\n", ((t_token *)word)->word);
	printf("		token type = %d\n\t}\n", ((t_token *)word)->type);
}
