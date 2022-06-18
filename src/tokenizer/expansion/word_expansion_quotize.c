/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion_quotize.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 05:15:00 by hseong            #+#    #+#             */
/*   Updated: 2022/06/18 17:06:39 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

#include "parser/token_recognition.h"

static int	count_words(char *str);

char	*convert_str_to_quoted(char *string)
{
	char	*new_string;
	size_t	idx;
	size_t	count;
	size_t	jdx;

	count = count_words(string);
	new_string = malloc(ft_strlen(string) + 2 * count + 1);
	idx = 0;
	jdx = 0;
	if (string[0] && !is_ifs(string[0]))
		new_string[jdx++] = '\'';
	while (string[idx])
	{
		if (idx > 0 && is_ifs(string[idx - 1])
			&& string[idx] && !is_ifs(string[idx]))
			new_string[jdx++] = '\'';
		new_string[jdx++] = string[idx];
		if (!is_ifs(string[idx])
			&& (is_ifs(string[idx + 1]) || string[idx + 1] == 0))
			new_string[jdx++] = '\'';
		++idx;
	}
	new_string[jdx] = 0;
	return (new_string);
}

int	count_words(char *str)
{
	int		count;

	count = 0;
	while (*str)
	{
		if (!is_ifs(*str) && (is_ifs(str[1]) || str[1] == 0))
			++count;
		++str;
	}
	return (count);
}
