/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:59:11 by gson              #+#    #+#             */
/*   Updated: 2022/06/03 18:26:54 by gson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

long long	ft_atoll(char *str, int *error)
{
	unsigned long long	num;
	unsigned long long	temp;
	long long			ret;
	int					neg;

	neg = *str == '-';
	str += (neg || *str == '+');
	num = 0;
	temp = 0;
	while (ft_isdigit(*str) && temp <= num)
	{
		temp = num;
		num = 10 * num + *str++ - 48;
	}
	if ((temp > num || num > LLONG_MAX) && error != NULL)
	{
		*error = -1;
		return ((LLONG_MAX * !neg + (-LLONG_MAX - 1) * neg));
	}
	ret = (1 - 2 * neg) * (num);
	return (ret);
}
