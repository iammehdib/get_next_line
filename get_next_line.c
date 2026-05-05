/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchet <mbuchet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 20:05:35 by mbuchet           #+#    #+#             */
/*   Updated: 2026/05/05 03:26:59 by mbuchet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static void	fill_buffer(t_buffer *buf, size_t new_size)
{
	size_t	cut_head;
	size_t	index;

	if (new_size > buf->size)
		cut_head = 0;
	else
		cut_head = buf->size - new_size;
	index = 0;
	while (index < new_size)
	{
		buf->content[index] = buf->content[cut_head + index];
		index++;
	}
	buf->content[new_size] = 0;
	buf->size = new_size;
	buf->current_read = 0;
}

static char	*extract_line(t_buffer *buf)
{
	char	*line;

	if (buf->content == NULL)
		return (NULL);
	while (buf->current_read < buf->size)
	{
		if (buf->content[buf->current_read] == '\n')
			break ;
		buf->current_read++;
	}
	if (buf->current_read == buf->size)
		return (NULL);
	line = malloc(sizeof(char) * (++buf->current_read + 1));
	if (line == NULL)
		return (NULL);
	line[buf->current_read] = 0;
	ft_strlcpy(line, buf->content, buf->current_read);
	fill_buffer(buf, buf->size - buf->current_read);
	return (line);
}

static ssize_t	current_read_line(t_buffer *buf, int fd)
{
	ssize_t	bytes_read;

	buffer_realloc_head(buf, buf->size + BUFFER_SIZE);
	bytes_read = read(fd, buf->content + buf->size, BUFFER_SIZE);
	if (bytes_read != -1)
		buf->size += bytes_read;
	return (bytes_read);
}

static char	*get_next_line_end(t_buffer *buf, char *line)
{
	if (buf->size == 0)
	{
		free_buf(buf);
		return (NULL);
	}
	buffer_realloc_head(buf, buf->size + 1);
	line = buf->content;
	line[buf->size] = 0;
	buf->content = NULL;
	free_buf(buf);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_buffer	buf = {.content = 0, .size = 0, .current_read = 0};
	ssize_t			result_read;
	char			*line;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		line = extract_line(&buf);
		if (line != NULL)
			break ;
		result_read = current_read_line(&buf, fd);
		if (result_read == -1 || result_read == 0)
		{
			line = get_next_line_end(&buf, line);
			break ;
		}
	}
	return (line);
}
