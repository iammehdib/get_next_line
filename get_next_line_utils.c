/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchet <mbuchet@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 18:31:40 by mbuchet           #+#    #+#             */
/*   Updated: 2026/04/23 17:27:20 by mbuchet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>

size_t	ft_strlen(const char *str)
{
	size_t	str_length;

	str_length = 0;
	while (str[str_length])
	{
		if (str[str_length] == '\n')
			return (str_length);
		str_length++;
	}
	return (str_length);
}

int	ft_is_contain_charset(int c, char const *set)
{
	size_t	index;

	index = 0;
	while (set[index])
	{
		if (c == set[index++])
			return (1);
	}
	return (0);
}

char	*ft_gnl_remove_nl(char str[], int increment)
{
	size_t	index;

	if (increment == -1)
		 index = ft_strlen(str);
	else if (increment == 1)
		index = 0;
	while (str[index] == '\n')
	{
		if (increment == -1)
			index--;
		else if (increment == 1)
			index++;
		str[index] = 0;
	}
	return (str);
}

char	*ft_strjoin(char const *str, char const *add_str)
{
	char	*str_final;
	size_t	str_index;
	size_t	index;

	if (str == NULL)
		str = "";
	if (add_str == NULL)
		return (NULL);
	str_final = malloc(sizeof(char) * ((ft_strlen(str) + ft_strlen(add_str)) + 1));
	if (str == NULL)
		return (NULL);
	str_index = 0;
	index = 0;
	while (str[index])
		str_final[str_index++] = str[index++];
	index = 0;
	while (index < ft_strlen(add_str))
		str_final[str_index++] = add_str[index++];
	str_final[str_index] = 0;
	return (str_final);
}

void	ft_remove_below_nl(char *str)
{
	size_t	index;

	index = 0;
	while (str[index])
	{
		index++;
	}
}
