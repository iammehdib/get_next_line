/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchet <mbuchet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 20:05:35 by mbuchet           #+#    #+#             */
/*   Updated: 2026/05/02 19:18:19 by mbuchet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Function s'il trouve une ligne la supprimer du buffer
void	delete_buffer(t_buffer *buf)
{
	size_t	new_size;
	char	*new_content;

	new_size = buf->size - buf->current_read;
	if (new_size == 0)
	{
		free_buf(buf);
		return ;
	}
	new_content = malloc(sizeof(char) * (new_size));
	if (new_content == NULL)
		return ;
	ft_strlcpy(new_content, buf->content + buf->current_read, new_size);
	free(buf->content);
	buf->content = new_content;
	buf->size = new_size;
	buf->current_read = 0;
}

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
	delete_buffer(buf);
	return (line);
}

// Function qui rmplit le buffer en lisant la suite
ssize_t	current_read_line(t_buffer *buf, int fd)
{
	char	*new_buf;
	ssize_t	bytes_read;

	new_buf = malloc(sizeof(char) * (buf->size + BUFFER_SIZE));
	if (new_buf == NULL)
		return (-1);
	if (buf->size > 0)
	{
		ft_strlcpy(new_buf, buf->content, buf->size);
		free(buf->content);
	}
	buf->content = new_buf;
	bytes_read = read(fd, buf->content + buf->size, BUFFER_SIZE);
	if (bytes_read == 0 || bytes_read == -1)
	{
		free(buf->content);
		buf->content = NULL;
	}
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
			if (result_read == 0)
				return (NULL);
			line = malloc(sizeof(char) + (buf.size + 1));
			if (line == NULL)
				return (NULL);
			ft_strlcpy(line, buf.content, buf.size);
			line[buf.size] = 0;
			free_buf(&buf);
		}
	}
	return (line);
}
