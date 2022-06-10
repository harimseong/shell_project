/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 22:31:10 by hseong            #+#    #+#             */
/*   Updated: 2022/06/11 03:07:54 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

void	*get_word_from_token(void *content);
void	*get_key_from_env(void *content);
char	*get_value_from_env(t_dlist *env_list, const char *key);

#endif
