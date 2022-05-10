/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 21:21:20 by hseong            #+#    #+#             */
/*   Updated: 2022/03/23 15:43:48 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	set_word(int c, t_word *num);

// int32 0A0B0C0D	> i [0A], i+1 [0B], i+2 [0C], i+3[0D]
// big endian		: msb is at lower address.
// int32 0A0B0C0D	> i [0D], i+1 [0C], i+2 [0B], i+3[0A]
// little endian	: lsb is at lower address.
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	t_word			*word;
	t_word			num;
	size_t			idx;

	ptr = (unsigned char *)b;
	idx = len % (8 * WORD_BYTES);
	while (idx--)
		*ptr++ = (unsigned char)c;
	len /= (8 * WORD_BYTES);
	word = (t_word *)ptr;
	idx = 0;
	set_word(c, &num);
	while (idx < len)
		word[idx++] = num;
	return (b);
}

void	set_word(int c, t_word *num)
{
	size_t		idx;
	t_uint64	long_c;

	long_c = (t_uint64)c;
	long_c = long_c + (long_c << 32);
	idx = 0;
	while (idx < WORD_BYTES)
		num->byte[idx++] = long_c;
}
