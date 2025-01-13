/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporzig <fporzig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:26:00 by fporzig           #+#    #+#             */
/*   Updated: 2024/12/19 13:26:30 by fporzig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
    int     fd;
    char    *line;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <file1> <file2> ... <fileN>\n", argv[0]);
        return (1);
    }
    for (int i = 1; i < argc; i++)
    {
        fd = open(argv[i], O_RDONLY);
        if (fd < 0)
        {
            perror("Error opening file");
            continue;
        }
        line = get_next_line(fd);
        while (line)
        {
            printf("%s", line);
            free(line);
            line = get_next_line(fd);
        }
        close(fd);
    }
    return (0);
}

// gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32 -o test get_next_line.c get_next_line_utils.c test.c
// ./test <file1> <file2> ... <fileN>
