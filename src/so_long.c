/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:39:01 by filferna          #+#    #+#             */
/*   Updated: 2024/09/28 14:32:18 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_gui(t_gui *gui)
{
	mlx_destroy_image(gui->mlx, gui->player.img);
	mlx_destroy_image(gui->mlx, gui->chest.img);
	mlx_destroy_image(gui->mlx, gui->cave.img);
	mlx_destroy_image(gui->mlx, gui->wall.img);
	mlx_destroy_image(gui->mlx, gui->floor.img);
	mlx_destroy_image(gui->mlx, gui->bg.img);
	mlx_destroy_window(gui->mlx, gui->win);
	mlx_destroy_display(gui->mlx);
	free(gui->mlx);
}

void	init_imgs(t_gui *gui)
{
	int	wid;

	gui->player.img = mlx_xpm_file_to_image(gui->mlx,
			"../textures/wizard.xpm", &wid, &wid);
	gui->player.addr = mlx_get_data_addr(gui->player.img,
			&gui->player.bpp, &gui->player.llen, &gui->player.endian);
	gui->chest.img = mlx_xpm_file_to_image(gui->mlx,
			"../textures/chest.xpm", &wid, &wid);
	gui->chest.addr = mlx_get_data_addr(gui->chest.img,
			&gui->chest.bpp, &gui->chest.llen, &gui->chest.endian);
	gui->cave.img = mlx_xpm_file_to_image(gui->mlx,
			"../textures/cave.xpm", &wid, &wid);
	gui->cave.addr = mlx_get_data_addr(gui->cave.img,
			&gui->cave.bpp, &gui->cave.llen, &gui->cave.endian);
	gui->wall.img = mlx_xpm_file_to_image(gui->mlx,
			"../textures/wall.xpm", &wid, &wid);
	gui->wall.addr = mlx_get_data_addr(gui->wall.img,
			&gui->wall.bpp, &gui->wall.llen, &gui->wall.endian);
	gui->floor.img = mlx_xpm_file_to_image(gui->mlx,
			"../textures/floor.xpm", &wid, &wid);
	gui->floor.addr = mlx_get_data_addr(gui->floor.img,
			&gui->floor.bpp, &gui->floor.llen, &gui->floor.endian);
	gui->bg.img = mlx_new_image(gui->mlx, gui->map_x * 32, gui->map_y * 32);
	gui->bg.addr = mlx_get_data_addr(gui->bg.img,
			&gui->bg.bpp, &gui->bg.llen, &gui->bg.endian);
}

void	init_numbers(t_gui *gui, char **map)
{
	int	y;
	int	x;

	gui->moves = 0;
	y = 0;
	x = -1;
	while (map[y][++x])
		gui->map_x = x;
	gui->map_x += 1;
	while (map[++y])
		gui->map_y = y;
	gui->map_y += 1;
	x = -1;
	y = -1;
	gui->collectables = 0;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			if (map[y][x] == 'C')
				gui->collectables += 1;
	}
}

void	init(t_gui *gui, char **map)
{
	gui->p_y = -1;
	while (map[++gui->p_y])
	{
		gui->p_x = 0;
		while (map[gui->p_y][gui->p_x] != 'P' && map[gui->p_y][gui->p_x])
			gui->p_x++;
		if (map[gui->p_y][gui->p_x] == 'P')
			break ;
	}
	gui->mlx = mlx_init();
	init_numbers(gui, map);
	gui->map = map;
	init_imgs(gui);
	gui->player_c = 0;
	gui->win = mlx_new_window(gui->mlx,
			gui->map_x * 32, gui->map_y * 32, "GAME");
}

int	main(int ac, char **av)
{
	int		fd;
	char	**line;
	t_gui	gui;

	if (ac != 2)
		return (ft_printf("Error in use ex: ./so_long ..maps/map.ber\n"));
	fd = open(file_name(av[1]), O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error reading file\n"), 0);
	line = get_arr(fd);
	if (!line)
		return (ft_printf("empty map\n"));
	fd = -1;
	if (check_map(line) || !confirm_imgs())
		return (free_matrix(line), 0);
	init(&gui, line);
	game_loop(&gui);
	return (free_matrix(line), 0);
}
