/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 22:35:48 by hseong            #+#    #+#             */
/*   Updated: 2022/03/31 22:28:42 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# define BUFFER_SIZE (256)

# ifndef INT_MAX
#  define INT_MAX 2147483647
# endif

typedef struct s_line
{
	int				cap;
	int				size;
	unsigned char	*str;
}					t_line;

typedef struct s_buf
{
	int				fd;
	int				size;
	unsigned char	*str;
}					t_buf;

#endif
