/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchet <mbuchet@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 18:31:40 by mbuchet           #+#    #+#             */
/*   Updated: 2026/04/23 22:39:25 by mbuchet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <stdio.h>
size_t	ft_strlen(const char *str, int check_nl)
{
	size_t	str_length;

	str_length = 0;
	if (check_nl == 1)
	{
		while (str[str_length] || str[str_length] == '\n')
			str_length++;
	}
	else
	{
		while (str[str_length])
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

void	ft_gnl_remove_nl(char *str)
{
	size_t	index;
	size_t	i;

	index = 0;
	while ( str[index] != '\n')
		index++;
	i = 0;
	while (index < ft_strlen(str, 0))
	{
		str[i++] = str[index++];
	}
	str[i] = 0;
}

#include <stdio.h>

char	*ft_strjoin(char const *str, char const *add_str)
{
	char	*str_final;
	size_t	str_index;
	size_t	index;

	if (str == NULL)
		str = "";
	if (add_str == NULL)
		add_str = "";
	str_final = malloc(sizeof(char) * ((ft_strlen(str, 0) + ft_strlen(add_str, 1)) + 1));
	if (str_final == NULL)
		return (NULL);
	str_index = 0;
	index = 0;
	while (str[index])
		str_final[str_index++] = str[index++];
	index = 0;
	while (index < ft_strlen(add_str, 1))
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
