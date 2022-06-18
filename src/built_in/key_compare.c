/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_compare.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:40:48 by hseong            #+#    #+#             */
/*   Updated: 2022/06/18 18:47:19 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int	key_compare(const void *node1, const void *node2)
{
	return (ft_strcmp(((t_env *)node1)->key, ((t_env *)node2)->key));
}
