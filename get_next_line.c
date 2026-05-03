/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchet <mbuchet@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 20:05:35 by mbuchet           #+#    #+#             */
/*   Updated: 2026/05/03 18:39:22 by mbuchet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Function qui check si \n ou 0 dans le str et qui extrait celui-ci
char	*extract_line(t_buffer *buf)
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
		return (0);
	line = malloc(sizeof(char) * (++buf->current_read + 1));
	if (line == NULL)
		return (NULL);
	line[buf->current_read] = 0;
	ft_strlcpy(line, buf->content, buf->current_read);
	buffer_realloc_head(buf, buf->size - buf->current_read);
	return (line);
}

// Function qui rmplit le buffer en lisant la suite
ssize_t	current_read_line(t_buffer *buf, int fd)
{
	ssize_t	bytes_read;

	buffer_realloc_head(buf, buf->size + BUFFER_SIZE);
	bytes_read = read(fd, buf->content + buf->size, BUFFER_SIZE);
	if (bytes_read != -1)
		buf->size += bytes_read;
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static t_buffer	buf = {.content = 0, .size = 0, .current_read = 0};
	ssize_t			result_read;
	char			*line;

	if (fd == -1)
		return (NULL);
	while (1)
	{
		line = extract_line(&buf);
		if (line != NULL)
			break ;
		result_read = current_read_line(&buf, fd);
		if (result_read == -1 || result_read == 0)
		{
			if (buf.size == 0)
				return (NULL);
			buffer_realloc_head(&buf, buf.size + 1);
			line = buf.content;
			line[buf.size] = 0;
			buf.content = NULL;
			free_buf(&buf);
			break ;
		}
	}
	return (line);
}
