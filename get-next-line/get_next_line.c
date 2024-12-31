#include "get_next_line.h"

static char	*read_line(int fd, char *buffer)
{
	char	temp[BUFFER_SIZE + 1];
	int		bytes_read;

	while (1)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read <= 0)
			break;
		temp[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, temp);
		if (!buffer)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break;
	}
	return (buffer);
}

static char	*extract_line(char **buffer)
{
	char	*line;
	char	*temp;
	size_t	i = 0;

	if (!(*buffer) || !(*buffer)[0])
		return (NULL);
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	line = ft_substr(*buffer, 0, i + 1);
	temp = ft_strdup((*buffer)[i] == '\n' ? &(*buffer)[i + 1] : "");
	free(*buffer);
	*buffer = temp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffers[MAX_FD];

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	buffers[fd] = read_line(fd, buffers[fd]);
	return (extract_line(&buffers[fd]));
}
