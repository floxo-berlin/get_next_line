/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporzig <fporzig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:53:20 by fporzig           #+#    #+#             */
/*   Updated: 2024/12/17 16:55:07 by fporzig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

char	*ft_next(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = (char *)malloc((ft_strlen(buffer) - i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i++;
	while (buffer[i])
		line[j++] = buffer[i++];
	line[j] = '\0';
	free(buffer);
	return (line);
}

char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = (char *)malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

int	read_and_update(int fd, char *buffer, char **res)
{
	int	byte_read;

	byte_read = read(fd, buffer, BUFFER_SIZE);
	if (byte_read == -1)
	{
		free(buffer);
		return (-1);
	}
	buffer[byte_read] = '\0';
	*res = ft_free(*res, buffer);
	return (byte_read);
}

char	*read_file(int fd, char *res)
{
	char	*buffer;
	int		byte_read;

	if (!res)
	{
		res = (char *)malloc(1 * sizeof(char));
		if (!res)
			return (NULL);
		res[0] = '\0';
	}
	buffer = allocate_buffer();
	if (!buffer)
		return (NULL);
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read_and_update(fd, buffer, &res);
		if (byte_read == -1)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_line(buffer);
	buffer = ft_next(buffer);
	return (line);
}
