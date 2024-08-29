#include "libft.h"

static void	free_matrix(char **line)
{
	int	a;

	a = 0;
	while (line[a])
	{
		free(line[a]);
		a++;
	}
	free (line);
}

int     ft_strclen(char *str, char c)
{
        int     i;

	if(!str)
		return (0);
        i = -1;
        while (str[++i])
                if(str[i] == c)
                        return (i + 1);
        return (i + 1);

}

static char	**m_matrix(char **line, char *stas)
{
	int	i;
	int	a;
	int	j;
	char	*stash;

	stash = stas;
	i = -1;
	a = 2;
	j = 0;
	while (stash[++i])
		if (stash[i] == '\n')
			a++;
	if (i < 1)
		return (NULL);
	line = (char **)malloc(sizeof(char *) * a);
	if (!line)
		return (NULL);
	a = 0;
	line[j] = (char *)malloc(sizeof(char) * ft_strclen(stash, '\n'));
	if(!line[j])
		return (NULL);
	while (*stash)
	{
		if (*stash == '\n')
		{
			line[j][a] = 0;
			stash++;
			j++;
			a = 0;
			line[j] = (char *)malloc(sizeof(char *) * ft_strclen(stash, '\n'));
			if(!line[j])
				return (free_matrix(line), NULL);
		}
		line[j][a] = stash[i];
		stash++;
		a++;
	}
	line[j][a] = 0;
	j++;
	line[j] = NULL;
	return (line);
}

static char	*join(char *s1, char *s2)
{
	char	*new_str;
	int	i;
	int	a;

	if (!s2 || !*s2)
		return (s1);
	i = ft_strclen(s1, 0);
	a = ft_strclen(s2, 0);
	new_str = (char *)malloc(sizeof(char) * (i + a) + 1);
	if(!new_str)
		return (NULL);
	a = -1;
	i = -1;
	if (s1 && *s1)
		while (s1[++i])
			new_str[i] = s1[i];
	while (s2[++a])
		new_str[i++] = s2[a];
	new_str[i] = 0;
	if(s1)
		free(s1);
	free(s2);
	return (new_str);
}

char	**get_arr(int fd)
{
	int		bytes_read;
	char		*buffer;
	char		**line;
	static char 	*stash;

	line = NULL;
	while (bytes_read != 0)
	{
		buffer = (char*)malloc(sizeof(char) * BUFFER_SIZE + 1);
			if(!buffer)
				return (free(stash), NULL);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		buffer[bytes_read] = 0;
		stash = join(stash, buffer);
	}
	line = m_matrix(line, stash);
	free(stash);
	return (line);
}


