#include <fcntl.h>

#ifndef GNL_H
#define GNL_H

char	**get_arr(int fd);
char	*join(char *s1, char *s2);
int	ft_strclen(char *str, char c);
char	**m_matrix(char **line, char *stas);
void	free_matrix(char **line);


#endif

