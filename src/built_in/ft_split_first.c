/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_first.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:16:11 by hseong            #+#    #+#             */
/*   Updated: 2022/06/22 21:19:19 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static size_t	get_count(const char *str, const char *delim);
static char		**alloc_words_one(const char *str, size_t count);
static char		**alloc_words_two(const char *str, size_t count);
static void		dealloc_words(char ***str_arr, size_t size);

char	**ft_split_first(const char *str, const char *delim)
{
	size_t	count;

	count = get_count(str, delim);
	if (count == 1)
		return (alloc_words_one(str, count));
	else
		return (alloc_words_two(str, count));
}

size_t	get_count(const char *str, const char *delim)
{
	size_t	count;

	count = 1;
	while (*str)
	{
		if (ft_strchr(delim, *str) != NULL && str[1] != 0)
		{
			count++;
			return (count);
		}
		++str;
	}
	return (count);
}

char	**alloc_words_one(const char *str, size_t count)
{
	char	**str_arr;
	size_t	str_idx;
	size_t	idx;

	str_arr = malloc(sizeof(char *) * (count + 1));
	str_arr[count] = NULL;
	str_idx = 0;
	while (str_idx < count)
	{
		idx = 0;
		while (str[idx] == '=')
			++str;
		while (str[idx] && str[idx] != '=')
			++idx;
		str_arr[str_idx] = ft_strndup(str, idx);
		if (str_arr[str_idx] == NULL)
			break ;
		str += idx;
		++str_idx;
	}
	if (str_idx != count)
		dealloc_words(&str_arr, str_idx);
	return (str_arr);
}

char	**alloc_words_two(const char *str, size_t count)
{
	char	**str_arr;
	char	*equal_pos;

	str_arr = malloc(sizeof(char *) * (count + 1));
	str_arr[count] = NULL;
	equal_pos = ft_strchr(str, '=');
	str_arr[0] = ft_strndup(str, equal_pos - str);
	++equal_pos;
	str = equal_pos;
	while (*equal_pos)
		++equal_pos;
	if (equal_pos == str)
		str_arr[1] = NULL;
	else
		str_arr[1] = ft_strndup(str, equal_pos - str);
	return (str_arr);
}

void	dealloc_words(char ***str_arr_ptr, size_t size)
{
	char		**str_arr;
	size_t		idx;

	str_arr = *str_arr_ptr;
	idx = 0;
	while (idx < size)
	{
		free(str_arr[idx]);
		++idx;
	}
	free(str_arr);
	*str_arr_ptr = NULL;
}
