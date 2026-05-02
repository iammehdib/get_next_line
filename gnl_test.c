/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchet <mbuchet@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 16:59:02 by mbuchet           #+#    #+#             */
/*   Updated: 2026/04/29 11:14:58 by mbuchet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "stdio.h"

int main(int argc, char **argv)
{
    int     fd;
    char    *line;
    int     count;

    count = 0;
    if (argc != 2)
    {
        printf("Veuillez mettre le nom du fichier (exemple: ./a.out t.txt).\n");
        return (0);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        printf("Erreur: Impossible d'ouvrir le fichier '%s'\n", argv[1]);
        return (1);
    }
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        printf("[%d] %s", count, line);
        free(line);
        count++;
    }

    close(fd);
    printf("\n--- FIN DE FICHIER ---\n");
    return (0);
}

