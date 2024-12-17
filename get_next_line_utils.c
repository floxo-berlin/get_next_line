#include "get_next_line.h"

// Function to find the length of a string
size_t  ft_strlen(const char *str)
{
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

// Function to find a character in a string
char    *ft_strchr(const char *s, int c)
{
    while (*s)
    {
        if (*s == (char)c)
            return (char *)s;
        s++;
    }
    if (*s == (char)c)
        return (char *)s;
    return NULL;
}

// Function to concatenate two strings
char    *ft_strjoin(char const *s1, char const *s2)
{
    size_t  len1 = ft_strlen(s1);
    size_t  len2 = ft_strlen(s2);
    char    *join = malloc(len1 + len2 + 1);
    if (!join)
        return NULL;
    size_t  i = 0;
    while (*s1)
        join[i++] = *s1++;
    while (*s2)
        join[i++] = *s2++;
    join[i] = '\0';
    return join;
}

// Function to create a substring from a string
char    *ft_substr(char const *s, unsigned int start, size_t len)
{
    char    *sub;
    size_t  i;

    if (start >= ft_strlen(s))
        return malloc(1);
    sub = malloc(len + 1);
    if (!sub)
        return NULL;
    i = 0;
    while (s[start + i] && i < len)
    {
        sub[i] = s[start + i];
        i++;
    }
    sub[i] = '\0';
    return sub;
}
