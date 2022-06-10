/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 04:25:20 by hseong            #+#    #+#             */
/*   Updated: 2022/06/10 21:26:36 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "constants.h"
#include "parser/token_recognition.h"
#include "cmd.h"

static t_node	*find_env(t_iterator *iterator);
static void		*extract_content(void *arg);
static void		special_expansion(t_iterator *iterator);

int	expand_word(t_iterator *iterator)
{
	t_node	*node;
	t_node	*expand_point;
	char	*env_value;
	t_dlist	*buf;

	buf = iterator->line;
	node = find_env(iterator);
	expand_point = buf->cur->next;
	if (node == NULL && (ft_isdigit(get_char(buf->cur))
			|| ft_strchr(SPECIAL_CHAR_LIST, get_char(buf->cur)) != NULL))
		// out of subject feature
		special_expansion(iterator);
	if (node != NULL)
	{
		env_value = ((t_env *)node->content)->value;
		while (*env_value)
		{
			insert_at(buf, expand_point, ft_strndup(env_value++, 1));
			++iterator->len;
		}
	}
	buf->cur = buf->cur->next;
	erase_at(buf, buf->cur->prev, free);
	if (buf->cur->prev)
		move_front(buf);
	return (node == NULL);
}

t_node	*find_env(t_iterator *iterator)
{
	char	target;
	char	*expression;
	t_node	*node;
	size_t	idx;

	node = iterator->line->cur->next;
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
	expression = dlist_to_string(iterator->line->cur->next, idx);
	iterator->len -= idx + 1;
	while (idx--)
		erase_at(iterator->line, iterator->line->cur->next, free);
	node = dlist_find_content(iterator->env_list, expression,
			ft_strlen(expression) + 1, extract_content);
	free(expression);
	return (node);
}

void	*extract_content(void *arg)
{
	t_env	*env_node;

	env_node = arg;
	return (env_node->key);
}

void	special_expansion(t_iterator *iterator)
{
	(void)iterator;
}
