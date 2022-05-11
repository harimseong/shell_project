/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_type.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 19:05:47 by hseong            #+#    #+#             */
/*   Updated: 2022/05/11 15:16:14 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TYPE_H
# define MINISHELL_TYPE_H

# include <sys/_types/_size_t.h>

# define ULLINT unsigned long long int
# define LLINT long long int

typedef ULLINT	t_uint64;
typedef LLINT	t_int64;

typedef struct s_token
{
	int		type;
	char	*token;
	t_int64	len;
}				t_token;

#endif
