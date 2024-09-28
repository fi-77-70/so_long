/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:24:15 by filferna          #+#    #+#             */
/*   Updated: 2024/09/28 14:21:26 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	dup_arr_2(char **dup, char **map)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = 0;
		while (map[y][x])
			x++;
		if (x > 0)
			dup[y] = (char *)malloc(sizeof(char) * x + 1);
	}
}

char	**dup_arr(char **map)
{
	int		x;
	int		y;
	char	**dup;

	y = 0;
	while (map[y])
		y++;
	dup = (char **)malloc(sizeof(char *) * (y + 1));
	dup_arr_2(dup, map);
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

int	check_numbers(char **map)
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
		{
			if (map[y][x] != 'P' && map[y][x] != 'C'
			&& map[y][x] != 'E' && map[y][x] != '1' && map[y][x] != '0')
				goals++;
			if (x == 0 && map[y][x] != '1')
				goals++;
			if (y == 0 && map[y][x] != '1')
				goals++;
			if (map[y + 1] == NULL && map[y][x] != '1')
				goals++;
		}
		if (map[y][x - 1] != '1')
			goals++;
	}
	return (goals);
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
			if (map[y][x] == 'P')
				p += 3;
			if (map[y][x] == 'C')
				c = 1;
			if (map[y][x] == 'E')
				e += 4;
		}
	}
	return (p + c + e);
}

void	free_matrix(char **line)
{
	int	i;

	i = 0;
	if (!line)
		return ;
	while (line[i])
		free(line[i++]);
	free(line);
}
