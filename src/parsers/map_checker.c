/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:39:42 by filferna          #+#    #+#             */
/*   Updated: 2024/09/24 17:10:27 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (y < 3)
		return (0);
	y = -1;
	while (map[y + 1][x])
		x++;
	max_x = x;
	if (x < 2)
		return (0);
	while (map[++y])
	{
		x = 0;
		while (map[y][x])
			x++;
		if (x != max_x)
			return (0);
	}
	return (1);
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
			if (map[y][x] == 'P' || map[y][x] == 'C' || map[y][x] == 'E')
				goals++;
	}
	return (goals);
}

int	flood_map(char **field, int y, int x, int *pos)
{
	int	a;
	int	b;

	a = pos[0];
	b = pos[1];
	field[y][x] = 'F';
	if (field[y + 1][x] != '1' && field[y + 1][x] != 'F')
		flood_map(field, y + 1, x, pos);
	if (field[y][x + 1] != '1' && field[y][x + 1] != 'F')
		flood_map(field, y, x + 1, pos);
	if (field[y - 1][x] != '1' && field[y - 1][x] != 'F')
		flood_map(field, y - 1, x, pos);
	if (field[y][x - 1] != '1' && field[y][x - 1] != 'F')
		flood_map(field, y, x - 1, pos);
	if (y != a || x != b)
		return (0);
	if (check_goals(field))
		return (1);
	else
		return (0);
}

int	check_essentials(char **map, int y, int x)
{
	int		result;
	char	**dup;
	int		pos[2];

	pos[0] = y;
	pos[1] = x;
	dup = NULL;
	result = check_letters(map);
	if (check_numbers(map))
		return (ft_printf("Error in map format\n"), 0);
	if (result != 8)
		return (ft_printf("Error, something missing in map\n"), 0);
	dup = dup_arr(map);
	if (flood_map(dup, y, x, pos))
		return (free_matrix(dup), ft_printf("Error, map format\n"), 0);
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
