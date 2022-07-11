/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:31:56 by hseong            #+#    #+#             */
/*   Updated: 2022/07/11 16:58:07 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser/token.h"

int	token_word_cmp(const t_token *first_tok, const t_token *second_tok)
{
	return (ft_strncmp(first_tok->word, second_tok->word,
		ft_strlen(second_tok->word) + 1));
}
