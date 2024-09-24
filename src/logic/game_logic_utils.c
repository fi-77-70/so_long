/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:13:12 by filferna          #+#    #+#             */
/*   Updated: 2024/09/24 17:18:39 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	really_close(t_gui *gui)
{
	return (free_gui(gui), free_matrix(gui->map), exit(1), 0);
}

void	make_map(t_gui *gui)
{
	int	y;
	int	x;

	y = -1;
	while (gui->map[++y])
	{
		x = -1;
		while (gui->map[y][++x])
		{
			if (gui->map[y][x] == '0' || gui->map[y][x] == 'C'
			|| gui->map[y][x] == 'E' || gui->map[y][x] == 'P')
				put_tiles(&gui->background, &gui->floor, y * 32, x * 32);
			if (gui->map[y][x] == '1')
				put_tiles(&gui->background, &gui->wall, y * 32, x * 32);
			if (gui->map[y][x] == 'C')
				put_tiles(&gui->background, &gui->chest, y * 32, x * 32);
			if (gui->map[y][x] == 'E')
				put_tiles(&gui->background, &gui->cave, y * 32, x * 32);
		}
	}
}

void	move_player(t_gui *gui, int y, int x)
{
	if (gui->map[gui->p_y + y][gui->p_x + x] != '1')
	{
		if (gui->map[gui->p_y][gui->p_x] == 'C')
		{
			gui->player_c += 1;
			gui->map[gui->p_y][gui->p_x] = '0';
			make_map(gui);
		}
		gui->p_y = gui->p_y + y;
		gui->p_x = gui->p_x + x;
		gui->moves += 1;
		ft_printf("number of moves --> [%d]\n", gui->moves);
	}
	return ;
}
