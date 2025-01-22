#include "get_next_line.h"

size_t ft_strlen(const char *s)
{
    size_t len = 0;
    while (s && s[len])
        len++;
    return len;
}

char *ft_strchr(const char *s, int c)
{
    if (!s)
        return NULL;
    while (*s) {
        if (*s == (char)c)
            return (char *)s;
        s++;
    }
    return NULL;
}

char *ft_strjoin(char const *s1, char const *s2)
{
    size_t len1;
    size_t len2;
	char *joined;
	size_t	i;
	size_t	j;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
    joined = malloc(len1 + len2 + 1);
    if (!joined)
        return NULL;
    i = -1;
    while (++i < len1)
        joined[i] = s1[i];
    j = 0;
    while (j < len2)
        joined[i++] = s2[j++];
    joined[i] = '\0';
    return joined;
}

char *ft_strdup(const char *s1)
{
    size_t len = ft_strlen(s1);
    char *copy = malloc(len + 1);
    if (!copy)
        return NULL;
    for (size_t i = 0; i < len; i++)
        copy[i] = s1[i];
    copy[len] = '\0';
    return copy;
}


char *ft_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;

    i = 0;
    while (i < n && src[i]) {
        dest[i] = src[i];
        i++;
    }
    while (i < n) {
        dest[i] = '\0';
        i++;
    }
    return dest;
}

