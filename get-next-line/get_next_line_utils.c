#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	size_t	len = 0;
	char	*dup;

	while (s1[len])
		len++;
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	for (size_t i = 0; i < len; i++)
		dup[i] = s1[i];
	dup[len] = '\0';
	return (dup);
}

char	*ft_strjoin(char *s1, const char *s2)
{
	size_t	len1 = 0, len2 = 0;
	char	*joined;

	if (s1)
		while (s1[len1])
			len1++;
	while (s2[len2])
		len2++;
	joined = (char *)malloc(len1 + len2 + 1);
	if (!joined)
		return (NULL);
	for (size_t i = 0; i < len1; i++)
		joined[i] = s1[i];
	for (size_t i = 0; i < len2; i++)
		joined[len1 + i] = s2[i];
	joined[len1 + len2] = '\0';
	free(s1); // Libera la stringa precedente
	return (joined);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i = 0;

	if (!s)
		return (NULL);
	while (s[start + i] && i < len)
		i++;
	sub = (char *)malloc(i + 1);
	if (!sub)
		return (NULL);
	for (size_t j = 0; j < i; j++)
		sub[j] = s[start + j];
	sub[i] = '\0';
	return (sub);
}

char *ft_strchr(const char *s, int c)
{
    while (*s)
    {
        if (*s == (char)c)
            return ((char *)s);
        s++;
    }
    if (c == '\0')
        return ((char *)s);
    return (NULL);
}
