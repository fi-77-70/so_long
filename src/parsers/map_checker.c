#include "../header.h"

int	check_bounds(char **map)
{
	int	x;
	int	y;
	int	max_x;

	x = 0;
	y = 0;
	while (map[y])
		y++;
	if(y < 2)
		return (0);
	y = 0;
	while (map[y][x])
		x++;
	max_x = x;
	if (x < 2)
		return (0);
	while (map[y])
	{
		x = 0;
		while (map[y][x])
			x++;
		if(x != max_x)
			return (0);
		y++;
	}	
	return (1);
}

int	check_letters(char **map)
{
	int	x;
	int	y;
	int	p;
	int	c;
	int	e;

	y = -1;
	p = 0;
	c = 0;
	e = 0;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if(map[y][x] == 'P')
				p = 1;
			if(map[y][x] == 'C')
				c = 2;
			if(map[y][x] == 'E')
				e = 4;	
		}
	}
	return (p + c + e);
}

int	check_goals(char **map)
{
	int	y;
	int	x;
	int	goals;

	y = -1;
	goals = 0;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			if(map[y][x] == 'P' || map[y][x] == 'C' || map[y][x] == 'E')
				goals++;
	}
	return (goals);
}

int	flood_map(char **map, int y, int x)
{
	char **field;

	field = map;
	
	field[y][x] = 'F';

	if (field[y + 1][x] != '1' && field[y + 1][x] != 'F')
	       	flood_map(field, ++y, x);
	if (field[y][x + 1] != '1' && field[y][x + 1] != 'F')
		flood_map(field, y, ++x);
	if (field[y - 1][x] != '1' && field[y - 1][x] != 'F')
		flood_map(field, --y, x);
	if (field[y][x - 1] != '1' && field[y][x - 1] != 'F')
		flood_map(field, y, --x);
	if(check_goals(field))
		return (1);
	else
		return (0);
}


int	check_essentials(char **map, int y, int x)
{
	int	result;

	result = check_letters(map);
	if(result != 7)
		return (ft_printf("Error, map does not have all requiremnts"), 0);
	if(flood_map(map, y, x))
		return (ft_printf("Error, can't reach everything in map\n"), 0);
	return (1);
}

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
		if (map[y][x] == 'P')
			break ;
		y++;
	}
	if (!map[y])
		return (ft_printf("Error, map does not have a player\n"));
	if (!check_bounds(map))
		return (ft_printf("Error in map bounds\n"));
	if (!check_essentials(map, y, x))
		return (1);
	return (0);
}
