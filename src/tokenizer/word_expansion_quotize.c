/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion_quotize.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 05:15:00 by hseong            #+#    #+#             */
/*   Updated: 2022/06/15 19:52:06 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

#include "parser/token_recognition.h"

static int	count_words(char *str);

char	*convert_value_to_quoted(char *value)
{
	char	*new_value;
	size_t	idx;
	size_t	count;
	size_t	jdx;

	count = count_words(value);
	new_value = malloc(ft_strlen(value) + 2 * count + 1);
	idx = 0;
	jdx = 0;
	if (value[0] && !ft_isspace(value[0]))
		new_value[jdx++] = '\'';
	while (value[idx])
	{
		if (idx > 0 && ft_isspace(value[idx - 1])
			&& value[idx] && !ft_isspace(value[idx]))
			new_value[jdx++] = '\'';
		new_value[jdx++] = value[idx];
		if (!ft_isspace(value[idx])
			&& (ft_isspace(value[idx + 1]) || value[idx + 1] == 0))
			new_value[jdx++] = '\'';
		++idx;
	}
	new_value[jdx] = 0;
	return (new_value);
}

int	count_words(char *str)
{
	int		count;

	count = 0;
	while (*str)
	{
		if (!ft_isspace(*str) && (ft_isspace(str[1]) || str[1] == 0))
			++count;
		++str;
	}
	return (count);
}
