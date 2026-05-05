/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchet <mbuchet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 18:31:53 by mbuchet           #+#    #+#             */
/*   Updated: 2026/05/05 03:38:00 by mbuchet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);

typedef struct s_buffer
{
	char	*content;
	size_t	size;
	size_t	current_read;
}	t_buffer;

void	ft_strlcpy(char *dst, const char *src, size_t dsize);
void	free_buf(t_buffer *buf);
void	buffer_realloc_head(t_buffer *buf, size_t new_size);

#endif
