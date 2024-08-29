#include "header.h"


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
	while (line[i])
		ft_printf("%s\n", line[i++]);
	return (0);
}
