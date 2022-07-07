/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:34:49 by hseong            #+#    #+#             */
/*   Updated: 2022/07/07 20:35:13 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <dirent.h>
#include "libft.h"

#include "minishell.h"
#include "cmd.h"
#include "constants.h"
#include "parser/token_recognition.h"

int				str_cmp(const void *first, const void *second);
static t_dlist	*get_names(DIR *dir_stream);
static void		filter_names(t_iterator *iterator, t_dlist *name_list);
static int		insert_names(t_iterator *iterator, t_node *expand_point,
					t_dlist *name_list);
static int		pattern_matched(const char *pattern, const char *str);

int	expand_asterisk(t_iterator *iterator, t_node *expand_point, int token_type)
{
	char			current_working_dir[MAX_PATHNAME];
	DIR				*dir_stream;
	t_dlist			*name_list;

	if (check_token_type(token_type, TT_QUOTE_MASK))
			return (0);
	minishell_assert(getcwd(current_working_dir, MAX_PATHNAME) != NULL,
		__FILE__, __LINE__);
	dir_stream = opendir(current_working_dir);
	if (dir_stream == NULL)
		return (minishell_assert(0, __FILE__, __LINE__));
	name_list = get_names(dir_stream);
	filter_names(iterator, name_list);
	return (insert_names(iterator, expand_point, name_list));
}

/*
 * readdir error?
 */
t_dlist	*get_names(DIR *dir_stream)
{
	struct dirent	*dir_ent;
	t_dlist			*name_list;

	dir_ent = readdir(dir_stream);
	name_list = dlist_init();
	while (dir_ent)
	{
/*		if (dir_ent->d_name[0] == '.')
		{
			dir_ent = readdir(dir_stream);
			continue ;
		}
		*/
		push_back(name_list, ft_strndup(dir_ent->d_name,
				ft_strlen(dir_ent->d_name)));
		dir_ent = readdir(dir_stream);
	}
	dlist_mergesort(name_list, str_cmp);
	closedir(dir_stream);
	return (name_list);
}

int	insert_names(t_iterator *iterator, t_node *expand_point,
	t_dlist *name_list)
{
	char		*name;

	while (name_list->size)
	{
		name = get_front(name_list);
		while (*name)
			insert_at(iterator->line, expand_point, ft_strndup(name++, 1));
		insert_at(iterator->line, expand_point, ft_strndup(" ", 1));
		pop_front(name_list, free);
	}
	dlist_delete(name_list, free);
	return (0);
}

void	filter_names(t_iterator *iterator, t_dlist *name_list)
{
	char	*pattern;
	t_node	*node;
	t_node	*temp;

	pattern = dlist_to_string(iterator->line->head, iterator->line->idx);
	node = name_list->head;
	while (node != name_list->tail)
	{
		if (pattern_matched(pattern, node->content))
		{
			node = node->next;
			continue ;
		}
		temp = node;
		node = node->next;
		erase_at(name_list, temp, free);
	}
	if (name_list->size == 0)
		push_back(name_list, pattern);
	free(pattern);
}

int		pattern_matched(const char *pattern, const char *str)
{
	(void)pattern;
	(void)str;
	return (1);
}
