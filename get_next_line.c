/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchet <mbuchet@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 18:31:30 by mbuchet           #+#    #+#             */
/*   Updated: 2026/04/23 23:04:09 by mbuchet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

char	*get_next_line(int fd)
{
	static char last_lign[BUFFER_SIZE + 1];
	char 		*old_line;
	char 		*current_line;
	ssize_t		bytes_read;

	if (fd == -1)
		return (NULL);
	current_line = NULL;
	current_line = ft_strjoin(last_lign, current_line);
	bytes_read = read(fd, last_lign, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		old_line = current_line;
		current_line = ft_strjoin(old_line, last_lign);
		free(old_line);
		if (ft_is_contain_charset('\n', last_lign))
		{
			ft_gnl_remove_nl(last_lign);
			return (current_line);
		}
		bytes_read = read(fd, last_lign, BUFFER_SIZE);
	}
	if(bytes_read == 0 && !current_line)
		return(current_line);
	else
	 return  NULL;
}

int main(int argc, char **argv)
{
    int     fd;
    char    *line;

    if (argc != 2)
    {
        printf("erreur\n");
        return (0);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        printf("Erreur : Impossible d'ouvrir le fichier '%s'\n", argv[1]);
        return (1);
    }

    line = get_next_line(fd);
    while (line != NULL)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }

    close(fd);
    printf("\n--- FIN DE FICHIER ---\n");
    return (0);
}
