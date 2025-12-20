/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:32:13 by yel-moha          #+#    #+#             */
/*   Updated: 2025/01/30 10:32:13 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*dup;
	size_t	i;

	len = 0;
	i = 0;
	while (s1[len])
		len++;
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}

char	*ft_strjoin(char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*joined;
	int		i;
	int		j;

	len1 = 0;
	len2 = 0;
	i = -1;
	j = -1;
	if (s1)
		while (s1[len1])
			len1++;
	while (s2[len2])
		len2++;
	joined = (char *)malloc(len1 + len2 + 1);
	if (!joined)
		return (NULL);
	while (++i < (int)len1)
		joined[i] = s1[i];
	while (++j < (int)len2)
		joined[len1 + j] = s2[j];
	joined[len1 + len2] = '\0';
	free(s1);
	return (joined);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	while (s[start + i] && i < len)
		i++;
	sub = (char *)malloc(i + 1);
	if (!sub)
		return (NULL);
	while (j < i)
	{
		sub[j] = s[start + j];
		j++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_strchr(const char *s, int c)
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
