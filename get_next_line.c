/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporzig <fporzig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:48:24 by fporzig           #+#    #+#             */
/*   Updated: 2024/12/17 21:48:26 by fporzig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h> // For malloc, free

static char	*read_line(int fd, char *buffer, char *str)
{
	char	*temp;
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		buffer[bytes_read] = '\0';
		if (!str)
			str = ft_strdup("");
		temp = ft_strjoin(str, buffer);
		free(str);
		str = temp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (str);
}

static char	*extract_line(char **str)
{
	char	*line;
	char	*temp;
	char	*newline_pos;

	newline_pos = ft_strchr(*str, '\n');
	if (newline_pos)
	{
		line = ft_substr(*str, 0, newline_pos - *str + 1);
		temp = ft_strdup(*str + (newline_pos - *str + 1));
	}
	else
	{
		line = ft_strdup(*str);
		temp = NULL; // Set temp to NULL to indicate no more data
	}
	free(*str);
	*str = temp;
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	str = read_line(fd, buffer, str);
	free(buffer);
	if (!str)
		return (NULL);
	return extract_line(&str);
}
