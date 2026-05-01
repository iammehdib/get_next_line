/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchet <mbuchet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 16:21:44 by mbuchet           #+#    #+#             */
/*   Updated: 2026/05/01 19:42:41 by mbuchet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static	char	*get_next_line_utils(int bytes_read, char **current_line)
{
	if (bytes_read <= 0 && *current_line == NULL)
		return (*current_line);
	return (NULL);
}

static void	ft_gnl_remove_nl(char *str)
{
	size_t	index;
	size_t	i;

	index = 0;
	while (str[index] && str[index] != '\n')
		index++;
	if (str[index] == '\n')
		index++;
	i = 0;
	while (index < ft_strlen(str, 0))
		str[i++] = str[index++];
	while (i <= ft_strlen(str, 0))
		str[i++] = 0;
}

char	*get_next_line(int fd)
{
	static char	last_line[BUFFER_SIZE + 1];
	char		*old_line;
	char		*current_line;
	ssize_t		bytes_read;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	current_line = ft_strjoin(NULL, last_line);
	if (current_line == NULL)
		return (NULL);
	while (1)
	{
		bytes_read = read(fd, last_line, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		last_line[bytes_read] = 0;
		old_line = current_line;
		current_line = ft_strjoin(old_line, last_line);
		if (old_line != NULL)
			free(old_line);
		if (current_line == NULL)
			return (NULL);
		if (ft_is_contain_charset('\n', last_line) != -1)
		{
			ft_gnl_remove_nl(last_line);
			return (ft_substr(current_line, 0, ft_strlen(current_line, 0) - ft_strlen(last_line, 0)));
		}
	}
	return (get_next_line_utils(bytes_read, &current_line));
}
