/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 14:48:34 by hseong            #+#    #+#             */
/*   Updated: 2022/06/05 14:56:42 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

enum e_error_type
{
	ERR_ALLOC = 0x00000001,
	ERR_PARSER = 0x00000002
};

size_t	error_handler(int assertion, void *arg, int type);

#endif
