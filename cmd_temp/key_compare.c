/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_compare.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:40:48 by hseong            #+#    #+#             */
/*   Updated: 2022/05/26 20:24:11 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int	key_compare(void *content1, void *content2)
{
	return (ft_strcmp(((t_env *)content1)->key, ((t_env *)content2)->key));
}
