#include "get_next_line.h"

static char *get_line(char **stash)
{
    char    *line;
    char    *newline_pos;
    char    *temp;
    size_t  len;

    newline_pos = ft_strchr(*stash, '\n');
    if (newline_pos)
    {
        len = newline_pos - *stash + 1;
        line = ft_substr(*stash, 0, len);
        temp = ft_substr(*stash, len, ft_strlen(*stash) - len);
        free(*stash);
        *stash = temp;
    }
    else
    {
        line = ft_substr(*stash, 0, ft_strlen(*stash));
        free(*stash);
        *stash = NULL;
    }
    return line;
}

char    *get_next_line(int fd)
{
    static char *stash;
    char        buf[BUFFER_SIZE + 1];
    char        *temp;
    ssize_t     bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    while (!ft_strchr(stash, '\n'))
    {
        bytes_read = read(fd, buf, BUFFER_SIZE);
        if (bytes_read <= 0)
            break;
        buf[bytes_read] = '\0';
        if (!stash)
        {
            stash = ft_substr(buf, 0, bytes_read);
        }
        else
        {
            temp = ft_strjoin(stash, buf);
            free(stash);
            stash = temp;
        }
    }
    if (!stash || *stash == '\0')
        return NULL;
    return get_line(&stash);
}
