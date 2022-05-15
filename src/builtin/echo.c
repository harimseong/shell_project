/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 20:14:01 by gson              #+#    #+#             */
/*   Updated: 2022/05/14 00:13:03 by gson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <string.h>

int	echo(char *str)
{
	if (flag != n)
	{
		printf("%s\n", str);
	}
	else
		printf("%s", str);
	return (0);
}
