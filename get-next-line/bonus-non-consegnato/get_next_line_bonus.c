/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:24:44 by yel-moha          #+#    #+#             */
/*   Updated: 2025/01/29 18:24:44 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *buffer)
{
	char	*temp;
	int		bytes_read;

	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	while (1)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		temp[bytes_read] = '\0';
		if (!buffer)
			buffer = ft_strdup("");
		buffer = ft_strjoin(buffer, temp);
		if (!buffer)
			return (free(temp), NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(temp);
	if (bytes_read < 0 || !buffer)
		return (free(buffer), NULL);
	if (bytes_read == 0 && !buffer[0])
		return (free(buffer), NULL);
	return (buffer);
}

/*
static char	*read_to_buffer(int fd, char *temp, char *buffer)
{
	int	bytes_read;

	while (1)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		temp[bytes_read] = '\0';
		if (!buffer)
			buffer = ft_strdup("");
		buffer = ft_strjoin(buffer, temp);
		if (!buffer)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (buffer);
}

static char	*read_line(int fd, char *buffer)
{
	char	*temp;
	int		bytes_read;

	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	buffer = read_to_buffer(fd, temp, buffer);
	free(temp);
	if (!buffer)
		return (NULL);
	bytes_read = 0;
	if (buffer)
		while (buffer[bytes_read])
			bytes_read++;
	if (bytes_read == 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

*/
static char	*extract_line(char **buffer)
{
	char	*line;
	char	*temp;
	size_t	i;

	i = 0;
	if (!(*buffer) || !(*buffer)[0])
	{
		free(*buffer);
		*buffer = NULL;
		return (NULL);
	}
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	line = ft_substr(*buffer, 0, i + 1);
	if ((*buffer)[i] == '\n')
		temp = ft_strdup(&(*buffer)[i + 1]);
	else
		temp = ft_strdup("");
	free(*buffer);
	*buffer = temp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_line(fd, buffer);
	if (!buffer)
		return (NULL);
	return (extract_line(&buffer));
}
