/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 22:35:55 by hseong            #+#    #+#             */
/*   Updated: 2022/05/18 01:18:02 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

int		gnl_load_buf(t_buf *fd_buf, t_buf *buf, int fd);
int		gnl_save_buf(t_buf *fd_buf, t_buf *buf);
int		gnl_append(t_line *line, t_buf *buf);

char	*get_next_line(int fd)
{
	static t_buf	fd_buf[512];
	t_buf			buf;
	t_line			line;

	if (fd < 0 || BUFFER_SIZE < 1 || gnl_load_buf(fd_buf, &buf, fd))
		return (NULL);
	line = (t_line){128, 0, malloc(sizeof(char) * 128)};
	if (!line.str)
		return (NULL);
	while (gnl_append(&line, &buf))
	{
		buf.size = read(buf.fd * (buf.fd != INT_MAX), buf.str, BUFFER_SIZE);
		if (buf.size < 1)
			break ;
	}
	if (line.size < 1 || buf.size < 0
		|| (buf.size > 0 && gnl_save_buf(fd_buf, &buf)))
	{
		free(line.str);
		line.str = NULL;
	}
	free(buf.str);
	return ((char *)line.str);
}

int	gnl_load_buf(t_buf *fd_buf, t_buf *buf, int fd)
{
	int				idx;

	fd += INT_MAX * (!fd);
	*buf = (t_buf){fd, 0, malloc(sizeof(char) * BUFFER_SIZE)};
	if (!(buf->str))
		return (1);
	idx = 0;
	while (idx < 257 && fd_buf[idx].fd != fd)
		++idx;
	if (idx == 257)
		return (0);
	ft_memcpy(buf->str, fd_buf[idx].str, fd_buf[idx].size);
	buf->size = fd_buf[idx].size;
	free(fd_buf->str);
	fd_buf->fd = 0;
	fd_buf->str = NULL;
	return (0);
}

int	gnl_save_buf(t_buf *fd_buf, t_buf *buf)
{
	int		idx;

	idx = 0;
	while (idx < 257 && fd_buf[idx].fd != 0)
		++idx;
	if (idx == 257)
		return (1);
	fd_buf[idx].fd = buf->fd;
	fd_buf[idx].size = buf->size;
	fd_buf[idx].str = malloc(sizeof(char) * buf->size);
	ft_memcpy(fd_buf[idx].str, buf->str, buf->size);
	return (0);
}

int	gnl_append(t_line *line, t_buf *buf)
{
	unsigned char	*ptr;
	int				idx;

	if (line->size + buf->size >= line->cap)
	{
		line->cap = line->size + buf->size + 128;
		ptr = malloc(sizeof(char) * (line->cap));
		if (!ptr)
			return (line->size = 0);
		ft_memcpy(ptr, line->str, line->size + 1);
		free(line->str);
		line->str = ptr;
	}
	idx = 0;
	while (idx < buf->size && buf->str[idx++] != '\n')
		continue ;
	ft_memcpy(line->str + line->size, buf->str, idx);
	ft_memcpy(buf->str, buf->str + idx, buf->size - idx);
	line->size += idx;
	line->str[line->size] = 0;
	buf->size -= idx;
	return (!line->size || line->str[line->size - 1] != '\n');
}
