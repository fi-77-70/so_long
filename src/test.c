#include "header.h"


int main (int ac, char **av)
{
	int	i;
	int	len;

	
	i = 1;
	if (ac < 2)
		return (0);
	len = ft_strlen(av[1]);
	ft_printf("your first string is %d characters long\n", len);
	ft_printf("You input %d strings\n", ac);
	ft_printf("They are:\n");
	while (--ac)
		ft_printf("%s\n", av[i++]);
	return (0);
}
