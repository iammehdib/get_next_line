/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchet <mbuchet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 20:09:19 by mbuchet           #+#    #+#             */
/*   Updated: 2026/05/02 18:37:42 by mbuchet          ###   ########.fr       */
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
