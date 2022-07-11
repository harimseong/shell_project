/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:34:49 by hseong            #+#    #+#             */
/*   Updated: 2022/07/11 21:01:17 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <dirent.h>
#include "libft.h"

#include "minishell.h"
#include "cmd.h"
#include "constants.h"
#include "parser/token_recognition.h"

#define MAX_PATTERN_LEN (128)

int				token_word_cmp(const void *first, const void *second);
static t_dlist	*get_names(DIR *dir_stream);
static void		filter_names(const t_iterator *iterator, t_dlist *name_list);
static int		insert_names(t_iterator *iterator, t_node *expand_point,
					t_dlist *name_list);
static int		pattern_matched(char *pattern, t_token *str);
char			*get_sub_pattern(const char *pattern);
void			filter_special_cases(const char *pattern, t_dlist *name_list);
int				find_pattern(char **pattern_ptr, char **str_ptr);

int	expand_asterisk(t_iterator *iterator, t_node *expand_point, int token_type)
{
	char			current_working_dir[MAX_PATHNAME];
	DIR				*dir_stream;
	t_dlist			*name_list;

	(void)token_type;
	minishell_assert(getcwd(current_working_dir, MAX_PATHNAME) != NULL,
		__FILE__, __LINE__);
	dir_stream = opendir(current_working_dir);
	if (dir_stream == NULL)
		return (minishell_assert(0, __FILE__, __LINE__));
	name_list = get_names(dir_stream);
	filter_names(iterator, name_list);
	while (iterator->line->head != expand_point)
		pop_front(iterator->line, free);
	iterator->line->idx = 0;
	insert_names(iterator, expand_point, name_list);
	dlist_delete(name_list, delete_word_content);
	return (0);
}

t_dlist	*get_names(DIR *dir_stream)
{
	struct dirent	*dir_ent;
	t_dlist			*name_list;
	t_token			*name;

	dir_ent = readdir(dir_stream);
	name_list = dlist_init();
	while (dir_ent)
	{
		name = malloc(sizeof(*name));
		*name = (t_token){ft_strndup(dir_ent->d_name, ft_strlen(dir_ent->d_name)),
			dir_ent->d_type};
		push_back(name_list, name);
		dir_ent = readdir(dir_stream);
	}
	dlist_mergesort(name_list, token_word_cmp);
	closedir(dir_stream);
	return (name_list);
}

int	insert_names(t_iterator *iterator, t_node *expand_point,
	t_dlist *name_list)
{
	char		*name;

	while (name_list->size)
	{
		name = ((t_token *)get_front(name_list))->word;
		while (*name)
			insert_at(iterator->line, expand_point, ft_strndup(name++, 1));
		insert_at(iterator->line, expand_point, ft_strndup(" ", 1));
		pop_front(name_list, delete_word_content);
	}
	return (0);
}

void	filter_names(const t_iterator *iterator, t_dlist *name_list)
{
	char	*pattern;
	t_node	*node;
	t_node	*temp;

	pattern = dlist_to_string(iterator->line->head, iterator->line->idx);
	filter_special_cases(pattern, name_list);
	node = name_list->head;
	while (node != NULL)
	{
		if (pattern_matched(pattern, node->content))
		{
			node = node->next;
			continue ;
		}
		temp = node;
		node = node->next;
		erase_at(name_list, temp, delete_word_content);
	}
	if (name_list->size == 0)
	{
		push_back(name_list, malloc(sizeof(t_token)));
		*(t_token *)name_list->head->content = (t_token){pattern, 0};
	}
	else
		free(pattern);
}

/*
 * pattern matching for directory
 */
int		pattern_matched(char *pattern, t_token *name)
{
	char		*str;
	int			status;

	str = name->word;
	while (*str)
	{
		if (*pattern == '*')
		{
			status = find_pattern(&pattern, &str);
			if (status < 2)
				return (status);
		}
		if (*pattern != *str)
			return (0);
//		else if (*pattern == '/' && name->type != DT_DIR)
//			return (0);
		++pattern;
		++str;
	}
	while (*pattern == '*')
		++pattern;
	return (*pattern == '\0');
}

int	find_pattern(char **pattern_ptr, char **str_ptr)
{
	char		*pattern;
	char		*str;
	static char	pattern_buf[MAX_PATTERN_LEN] = {0, };
	int			idx;

	pattern = *pattern_ptr;
	str = *str_ptr;
	idx = 0;
	while (*pattern == '*')
		++pattern;
	while (pattern[idx] && pattern[idx] != '*')
	{
		pattern_buf[idx] = pattern[idx];
		++idx;
	}
	pattern_buf[idx] = 0;
	if (idx == 0)
		return (1);
	str = ft_strnstr(str, pattern_buf, ft_strlen(str));
	if (str == NULL)
		return (0);
	if (*pattern == '\0' && *str != '\0')
	{
		++*str_ptr;
		return (find_pattern(&pattern, str_ptr));
	}
	*pattern_ptr += idx;
	*str_ptr += idx;
	return (2);
}

void	filter_special_cases(const char *pattern, t_dlist *name_list)
{
	t_node	*node;
	t_token	*name;

	if (pattern[0] == '*')
	{
		node = name_list->head;
		while (node != name_list->tail)
		{
			name = node->content;
			if (name->word[0] == '.')
				node = erase_at(name_list, node, delete_word_content);
			else
				node = node->next;
		}
	}
}
