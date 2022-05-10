/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvpe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:01:20 by hseong            #+#    #+#             */
/*   Updated: 2022/05/10 18:23:00 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#define MAX_PATHNAME (1000)

void			*ft_memset(void *b, int c, size_t len);
size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);

static size_t	get_path_tab_size(void);

static const char	*g_path_table[] = {
	"/usr/bin/",
	"/bin",
	"/Users/hseong/42backup/core3/minishell",
	NULL
};

int	ft_execvpe(const char *filename, char *const *argv, char *const *envp)
{
	char	fullpath[MAX_PATHNAME + 1];
	size_t	table_size;
	size_t	idx;
	size_t	path_len;

	execve(filename, argv, envp);
	table_size = get_path_tab_size();
	idx = 0;
	while (idx < table_size)
	{
		ft_memset(fullpath, 0, MAX_PATHNAME + 1);
		path_len = ft_strlen(g_path_table[idx]);
		if (path_len + ft_strlen(filename) + 2 >= MAX_PATHNAME)
		{
			++idx;
			continue ;
		}
		ft_strlcpy(fullpath, g_path_table[idx], path_len + 1);
		if (fullpath[path_len - 1] != '/')
			fullpath[path_len] = '/';
		ft_strlcat(fullpath, filename, MAX_PATHNAME + 1);
		execve(fullpath, argv, envp);
		++idx;
	}
	return (-1);
}

static size_t	get_path_tab_size(void)
{
	size_t		size;

	size = 0;
	while (g_path_table[size])
		++size;
	return (size);
}
