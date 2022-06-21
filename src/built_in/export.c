/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:29:37 by gson              #+#    #+#             */
/*   Updated: 2022/06/21 16:05:12 by gson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"
#include "execute.h"

static int	check_arg_error(char **element, char *argv)
{
	if (check_identifier_first(element[0][0]) == -1)
	{
		printf("minishell: export: `%s': not a valid identifier\n", argv);
		free_str_arr(element);
		return (1);
	}
	if (is_contain_special(element[0]) == -1)
	{
		printf("minishell: export: `%s': not a valid identifier\n", argv);
		free_str_arr(element);
		return (1);
	}
	return (0);
}

static t_env	*make_new_env(char **element, char *argv)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	new_env->key = element[0];
	if (element[1] != 0)
	{
		new_env->value = element[1];
		new_env->has_equal = 1;
	}
	else if (ft_strchr(argv, '=') == NULL)
	{
		new_env->value = NULL;
		new_env->has_equal = 0;
	}
	else
	{
		new_env->value = NULL;
		new_env->has_equal = 1;
	}
	free(element);
	return (new_env);
}

int	export_args(t_dlist *envlist, char *argv)
{
	t_env	*new_env;
	char	**element;

	element = ft_split_first(argv, "=");
	if (check_arg_error(element, argv) == 1)
		return (1);
	if (check_identifier_first(element[0][0]) == 0
		&& ft_strlen(element[0]) == 1)
	{
		free_str_arr(element);
		return (0);
	}
	if (check_key_dup(envlist, element, argv) == 1)
		return (0);
	new_env = make_new_env(element, argv);
	push_back(envlist, new_env);
	return (0);
}
//	move '_' to last
//	t_env	*temp_env;
//
//	temp_env = envlist->tail->content;
//	envlist->tail->content = envlist->tail->prev->content;
//	envlist->tail->prev->content = temp_env;

int	export_no_args(t_dlist *envlist)
{
	t_dlist	*cp_envlist;
	t_env	*cur_env;

	cp_envlist = dlist_duplicate(envlist, copy_env_content);
	dlist_mergesort(cp_envlist, key_compare);
	cp_envlist->cur = cp_envlist->head;
	while (cp_envlist->cur != 0)
	{
		cur_env = (t_env *)cp_envlist->cur->content;
		if (cur_env->has_equal == 1 && cur_env->value != NULL)
			printf("declare -x %s=\"%s\"\n", cur_env->key, cur_env->value);
		else if (cur_env->has_equal == 1 && cur_env->value == NULL)
			printf("declare -x %s=\"\"\n", cur_env->key);
		else if (cur_env->has_equal == 0)
			printf("declare -x %s\n", cur_env->key);
		cp_envlist->cur = cp_envlist->cur->next;
	}
	dlist_delete(cp_envlist, delete_env_content);
	return (0);
}

int	export(t_dlist *envlist, int argc, char **argv)
{
	int		i;
	int		status;

	status = 0;
	if (argc == 1)
		export_no_args(envlist);
	else if (argc > 1)
	{
		i = 1;
		while (argv[i] != 0)
		{
			if (export_args(envlist, argv[i]) == 1)
				status = 1;
			i++;
		}
	}
	return (status);
}
