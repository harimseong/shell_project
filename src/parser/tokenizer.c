/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 21:26:50 by hseong            #+#    #+#             */
/*   Updated: 2022/05/25 21:37:59 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "constants.h"
#include "parser/tokenizer.h"

t_token	*get_token(t_input_line *input_line)
{
	int		cursor;

	cursor = input_line->str[input_line->pos];
	if (cursor == 0)
		return (NULL);
	if (ft_isalnum(cursor) == TRUE)
		return (get_word(input_line));
	el
}
