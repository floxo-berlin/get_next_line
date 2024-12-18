#include <fcntl.h> // For open
#include <unistd.h> // For close
#include <stdio.h> // For printf
#include <stdlib.h> // For free
#include "get_next_line.h"

int main(void)
{
	int fd;
	char *line;

	// Open the file and get the file descriptor
	fd = open("file.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}

	// Call get_next_line with the file descriptor
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}

	// Close the file descriptor
	close(fd);
	return (0);
}
