/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporzig <fporzig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:26:00 by fporzig           #+#    #+#             */
/*   Updated: 2025/01/14 13:44:14 by fporzig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		i;

	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <file1> <file2> ... <fileN>\n", argv[0]);
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		fd = open(argv[i], O_RDONLY);
		if (fd < 0)
		{
			perror("Error opening file");
			i++;
			continue ;
		}
		line = get_next_line(fd);
		while (line)
		{
			printf("%s", line);
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
		i++;
	}
	return (0);
}

// gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32 -o test get_next_line.c get_next_line_utils.c test.c
// ./test <file1> <file2> ... <fileN>
