#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define MAX_FD 1024 // Numero massimo di file descriptor

char	*get_next_line(int fd);
size_t  ft_strlen(const char *s);
char	*ft_strjoin(const char *s1, const char *s2);
char    *ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strncpy(char *dest, const char *src, size_t n);

#endif
