#include "../header.h"

int	check_map(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
				break ;
			x++;	
		}
		y++;
	}
	if(!check_bounds(map))
		return (ft_printf("Error in map bounds\n"));

}
