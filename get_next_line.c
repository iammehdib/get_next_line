/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchet <mbuchet@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 18:31:30 by mbuchet           #+#    #+#             */
/*   Updated: 2026/04/23 17:20:42 by mbuchet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>

char	*get_next_line(int fd)
{
	static char last_lign[BUFFER_SIZE + 1];
	char 		*old_line;
	char 		*current_line;

	if (fd == -1)
		return (NULL);
	current_line = NULL;
	while (read(fd, last_lign, BUFFER_SIZE) != 0)
	{
		old_line = current_line;
		free(current_line);
		current_line = ft_strjoin(old_line, last_lign);
		if (ft_is_contain_charset('\n', last_lign))
		{
			ft_gnl_remove_nl(last_lign, 0);
			break;
		}
	}
	return (current_line);
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Met 2 arguments bro.");
		return (0);
	}

	int fd = open(argv[1], 00);
	if (fd == -1)
	{
		printf("Le fichier '%s' existe pas.", argv[1]);
		return (0);
	}

	// Configurer ici la line de start et de end
	char *last_line;

	while (last_line != NULL)
	{
		last_line = get_next_line(fd);
		printf("%s\n", last_line);
		free(last_line);
		//get_next_line(fd);
	}
	close(fd);
	printf("\nFIN DE LINE");
}
