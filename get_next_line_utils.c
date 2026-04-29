/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchet <mbuchet@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 18:31:40 by mbuchet           #+#    #+#             */
/*   Updated: 2026/04/29 11:14:55 by mbuchet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t	ft_strlen(const char *str, int check_nl)
{
	size_t	str_length;

	str_length = 0;
	if (check_nl == 1)
	{
		while (str[str_length] && str[str_length] != '\n')
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
		if (set[index] == c)
			return (index);
		index++;
	}
	return (-1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	str_index;
	size_t	index;

	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";
	str = malloc(sizeof(char) * ((ft_strlen(s1, 0) + ft_strlen(s2, 0)) + 1));
	if (str == NULL)
		return (NULL);
	str_index = 0;
	index = 0;
	while (s1[index])
		str[str_index++] = s1[index++];
	index = 0;
	while (index < ft_strlen(s2, 0))
		str[str_index++] = s2[index++];
	str[str_index] = 0;
	return (str);
}

char	*ft_strdup(const char *s)
{
	size_t	index;
	size_t	str_lentgh;
	char	*str;

	index = 0;
	str_lentgh = ft_strlen(s, 0);
	str = malloc(sizeof(char) * (str_lentgh + 1));
	if (str == NULL)
		return (NULL);
	while (index < str_lentgh)
	{
		str[index] = s[index];
		index++;
	}
	str[index] = 0;
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	str_length;
	size_t	index;
	char	*str;

	if (s == NULL)
		return (NULL);
	str_length = ft_strlen(s, 0);
	if (start >= (unsigned int) str_length)
		return (ft_strdup(""));
	if ((str_length - start) < len)
		len = str_length - start;
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	index = 0;
	while (s[start] && (index < len))
		str[index++] = s[start++];
	str[index] = 0;
	return (str);
}
