/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:22:49 by hseong            #+#    #+#             */
/*   Updated: 2022/05/25 21:28:05 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "parser/parser.h"
#include "parser/tokenizer.h"

t_token	*parse(const char *line)
{
	t_input_line	input_line;
	t_token			*token;

	input_line = (t_input_line){(char *)line, 0};
	token = get_token(&input_line);
}
