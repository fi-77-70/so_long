#include "header.h"


void	free_matrix(char **line)
{
	int	i;

	i = 0;
	if(!line)
		return ;
	while (line[i])
		free(line[i++]);
	free(line);
}

int main (int ac, char **av)
{
	int	i;
	int	len;
	int	fd;
	char	**line;

	i = 1;
	if (ac < 2)
		return (0);
	len = ft_strlen(av[1]);
	ft_printf("your first string is %d characters long\n", len);
	ft_printf("You input %d strings\n", ac);
	ft_printf("They are:\n");
	while (--ac)
		ft_printf("%s\n", av[i++]);
	ft_printf("SUCCESS\n");
	ft_printf("NOW TESTING MATRIX GETTING FOR MAP\n");
	fd = open("text", O_RDONLY);
	if (fd < 0)
		return (0);
	i = 0;
	line = get_arr(fd);
	if(!line)
		return (ft_printf("empty map\n"));
	while (line[i])
		ft_printf("%s\n", line[i++]);
	ft_printf("SUCCESS\n");
	i = -1;
	ft_printf("NOW_TESTING_MAP_PARSING\n");
	if (!check_map(line))
		ft_printf("MAP IS GOOD\n");
	while (line[++i])
	{
		len = 0;
                while (line[i][len] != 'P' && line[i][len])
			len ++;
		if (line[i][len] == 'P')
			break;
	}
	game_loop(line, i, len);
	free_matrix(line);
	return (0);
}
