/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchet <mbuchet@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 20:09:19 by mbuchet           #+#    #+#             */
/*   Updated: 2026/05/04 20:16:02 by mbuchet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_strlcpy(char *dst, const char *src, size_t dsize)
{
	size_t	index;

	index = 0;
	while (index < dsize)
	{
		dst[index] = src[index];
		index++;
	}
}

void	free_buf(t_buffer *buf)
{
	free(buf->content);
	buf->content = 0;
	buf->size = 0;
	buf->current_read = 0;
}

void	buffer_realloc_head(t_buffer *buf, size_t new_size)
{
	char	*new_content;
	size_t	cut_head;

	new_content = malloc(sizeof(char) * new_size);
	if (new_content == NULL)
		return ;
	if (new_size > buf->size)
		cut_head = 0;
	else
		cut_head = buf->size - new_size;
	buf->size = buf->size - cut_head;
	if (buf->content != NULL)
		ft_strlcpy(new_content, buf->content + cut_head, buf->size);
	free(buf->content);
	buf->content = new_content;
	buf->current_read -= cut_head;
}
