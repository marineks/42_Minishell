#ifndef GNL_H
# define GNL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

char	*f_strchr(char *s, int c);
char	*f_strjoin(char *s1, char *s2);
char	*f_strdup(char *s1);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);

#endif