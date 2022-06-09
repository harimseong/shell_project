/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 13:30:48 by gson              #+#    #+#             */
/*   Updated: 2022/06/03 13:31:18 by gson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int	is_contain_special(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (ft_isalnum(str[i]) || (str[i] == '_'))
			i++;
		else
			return (-1);
	}
	return (0);
}

int	check_identifier_first(char identifier)
{
	if (identifier == '_')
		return (0);
	if (ft_isalpha(identifier))
		return (1);
	return (-1);
}
