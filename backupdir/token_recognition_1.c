/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:36:10 by hseong            #+#    #+#             */
/*   Updated: 2022/06/09 16:16:01 by gson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "parser/token.h"
#include "parser/token_recognition.h"
#include "libft.h"

int	char_delimiter(t_iterator *iterator, t_token *token)
{
	++iterator->end;
	return (0);
}

int	char_less(t_iterator *iterator, t_token *token)
{
	int		idx;
	int		ret;

	idx = 0;
	ret = 0;
	while (idx < TABLE_SIZE)
	{
		ret = g_token_recog_tab[idx](iterator, token);
		++idx;
		if (ret == 0)
			return (0);
	}
	return (1);
}

/*
	if (token->type == TT_LESS)
	{
		token->type = TT_DLESS;
		return (0);
	}
	else if (token->type & 0xf0000000)
	{
	}
	else if ((token->type & 0x10) == TRUE)
		++iterator->end;
	else if (token->type == TT_EMPTY)
		token->type = TT_LESS;
	else if (token->type == TT_WORD)
	{
		--iterator->end;
		return (0);
	}
	return (1);
}
*/
int	char_greater(t_iterator *iterator, t_token *token)
{
	++iterator->end;
	if (token->type == TT_GREAT)
		token->type = TT_DGREAT;
	else if (token->type == TT_EMPTY)
		token->type = TT_GREAT;
	else if ((token->type & 0x10) == TRUE)
		++iterator->end;
	else
	{
		--iterator->end;
		return (0);
	}
	return (1);
}
