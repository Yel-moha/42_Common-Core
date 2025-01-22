# include "get_next_line.h"

char *extract_line(char **buffer)
{
	char *line;
	char *temp;
	char *new_line;

	new_line = ft_strchr(*buffer, '\n');
	if(new_line)
	{
		line = malloc(new_line - *buffer + 2);
		if (!line)
			return NULL;
		line[new_line - *buffer + 1] = '\0';
		temp = *buffer;
		*buffer = ft_strdup(new_line + 1);
		ft_strncpy(line, temp, new_line - temp + 1);
		free(temp);
	}
	else
	{
		line = ft_strdup(*buffer);
		free(*buffer);
		*buffer = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char *buffer;
	char		buf[BUFFER_SIZE + 1];
	int			bytes_read;
	char 		*new_buffer;

	if(fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
		return NULL;
	while(!ft_strchr(buffer, '\n') && (bytes_read = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[bytes_read] = '\0';
		new_buffer = ft_strjoin((const char *)buffer, (const char *)buf);
		//new_buffer = ft_strjoin(buffer, buf);
		free(buffer);
		buffer = new_buffer;
	}
	if (!buffer || (bytes_read < 0 && !buffer[0]))
	{
		free(buffer);
		buffer = NULL;
		return NULL;
	}
	return extract_line(&buffer);
}