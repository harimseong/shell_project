/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 04:25:20 by hseong            #+#    #+#             */
/*   Updated: 2022/06/06 14:42:35 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlinkedlist.h"
#include "libft.h"
#include "../cmd_temp/cmd.h"
#include "parser/token.h"
#include "parser/token_recognition.h"

static void		delete_char(void *arg);
static t_node	*find_env(t_iterator *iterator);

void	expand_word(t_iterator *iterator)
{
	t_node	*node;
	t_node	*expand_point;
	char	*env_value;

	node = find_env(iterator);
	expand_point = iterator->end->next;
	if (node != NULL)
	{
		env_value = ((t_env *)node->content)->value;
		while (*env_value)
			insert_at(iterator->line,
				expand_point, ft_strndup(env_value++, 1));
	}
	erase_at(iterator->line, iterator->end, delete_char);
}

t_node	*find_env(t_iterator *iterator)
{
	char	target;
	char	*expression;
	t_node	*node;
	size_t	idx;

	node = iterator->end->next;
	target = get_char(node);
	if (ft_isalpha(target) == 0 && target != '_')
		return (NULL);
	idx = 0;
	while (target && (ft_isalnum(target) || target == '_'))
	{
		node = node->next;
		target = get_char(node);
		++idx;
	}
	expression = convert_list(iterator->end->next, idx);
	while (idx--)
		erase_at(iterator->line, iterator->end->next, delete_char);
	node = dlist_find_content(iterator->env_list, expression,
		ft_strlen(expression));
	free(expression);
	return (node);
}

void	delete_char(void *arg)
{
	free(arg);
}
