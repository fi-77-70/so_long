#include "../header.h"

char	**dup_arr(char **map)
{
	int	x;
	int	y;
	char 	**dup;

	y = 0;
	while (map[y])
		y++;
	dup = (char **)malloc(sizeof(char *) * (y + 1));
	y = -1;
	while (map[++y])
	{
		x = 0;
		while (map[y][x])
			x++;
		if(x > 0)
			dup[y] = (char *)malloc(sizeof(char) * x + 1);
	}
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			dup[y][x] = map[y][x];
		dup[y][x] = 0;
	}
	dup[y] = NULL;
	return (dup);
}

int	check_bounds(char **map)
{
	int	x;
	int	y;
	int	max_x;

	x = 0;
	y = 0;
	while (map[y])
		y++;
	if(y < 3)
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
				p += 3;
			if(map[y][x] == 'C')
				c = 1;
			if(map[y][x] == 'E')
				e += 4;	
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

int	flood_map(char **field, int y, int x, int a, int b)
{
	
	field[y][x] = 'F';

	if (field[y + 1][x] != '1' && field[y + 1][x] != 'F')
	       	flood_map(field, y + 1, x, a, b);
	if (field[y][x + 1] != '1' && field[y][x + 1] != 'F')
		flood_map(field, y, x + 1, a, b);
	if (field[y - 1][x] != '1' && field[y - 1][x] != 'F')
		flood_map(field, y - 1, x, a, b);
	if (field[y][x - 1] != '1' && field[y][x - 1] != 'F')
		flood_map(field, y, x - 1, a, b);
	if(y != a || x != b)
		return (0);
	if(check_goals(field))
		return (1);
	else
		return (0);
}

int	check_essentials(char **map, int y, int x)
{
	int	result;
	char	**dup;

	dup = NULL;
	result = check_letters(map);
	if(result != 8)
		return (ft_printf("Error, map does not meet all requiremnts"), 0);
	dup = dup_arr(map);
	if(flood_map(dup, y, x, y, x))
		return (free_matrix(dup), ft_printf("Error, can't reach everything in map\n"), 0);
	free_matrix(dup);
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
