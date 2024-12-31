#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define MAX_FD 1024 // Numero massimo di file descriptor

char	*get_next_line(int fd);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, const char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char    *ft_strchr(const char *s, int c);

#endif
