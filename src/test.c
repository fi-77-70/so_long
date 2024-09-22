/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:39:01 by filferna          #+#    #+#             */
/*   Updated: 2024/09/22 20:03:01 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void 	free_gui(t_gui *gui)
{
	mlx_destroy_image(gui->mlx, gui->player.img);
	mlx_destroy_image(gui->mlx, gui->chest.img);
	mlx_destroy_image(gui->mlx, gui->cave.img);
	mlx_destroy_image(gui->mlx, gui->wall.img);
	mlx_destroy_image(gui->mlx, gui->floor.img);
	mlx_destroy_image(gui->mlx, gui->background.img);
	mlx_destroy_window(gui->mlx, gui->win);
	mlx_destroy_display(gui->mlx);
	free(gui->mlx);
}

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

void	init_imgs(t_gui *gui)
{
	int	wid;
	int	hei;

	gui->player.img = mlx_xpm_file_to_image(gui->mlx, "../imgs/wizard.xpm", &wid, &hei);
	gui->player.addr = mlx_get_data_addr(gui->player.img, &gui->player.bits_p_pixel, &gui->player.line_len, &gui->player.endian);
	gui->chest.img = mlx_xpm_file_to_image(gui->mlx, "../imgs/chest.xpm", &wid, &hei);
	gui->chest.addr = mlx_get_data_addr(gui->chest.img, &gui->chest.bits_p_pixel, &gui->chest.line_len, &gui->chest.endian);
	gui->cave.img = mlx_xpm_file_to_image(gui->mlx, "../imgs/cave.xpm", &wid, &hei);
	gui->cave.addr = mlx_get_data_addr(gui->cave.img, &gui->cave.bits_p_pixel, &gui->cave.line_len, &gui->cave.endian);
	gui->wall.img = mlx_xpm_file_to_image(gui->mlx, "../imgs/wall.xpm", &wid, &hei);
	gui->wall.addr = mlx_get_data_addr(gui->wall.img, &gui->wall.bits_p_pixel, &gui->wall.line_len, &gui->wall.endian);
	gui->floor.img = mlx_xpm_file_to_image(gui->mlx, "../imgs/floor.xpm", &wid, &hei);
	gui->floor.addr = mlx_get_data_addr(gui->floor.img, &gui->floor.bits_p_pixel, &gui->floor.line_len, &gui->floor.endian);
	gui->background.img = mlx_new_image(gui->mlx, gui->map_x * 32, gui->map_y * 32);
	gui->background.addr = mlx_get_data_addr(gui->background.img, &gui->background.bits_p_pixel, &gui->background.line_len, &gui->background.endian);
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
			if(map[y][x] == 'C')
				gui->collectables += 1;
	}	
}

void	init(t_gui *gui, char **map, int y, int x)
{
	gui->mlx = mlx_init();
	init_numbers(gui, map);
	gui->map = map;
	gui->p_y = y;
	gui->p_x = x;
	init_imgs(gui);
	gui->player_c = 0;
	gui->win = mlx_new_window(gui->mlx, gui->map_x * 32, gui->map_y * 32, "GAME");

}

int main (int ac, char **av)
{
	int	i;
	int	len;
	int	fd;
	char	**line;
	t_gui	gui;

	if (ac != 2)
		return (ft_printf("Error -> correct use(so_long map_directory"));
	fd = open(av[1], O_RDONLY);
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
	else
		return(free_matrix(line), 0);
	while (line[++i])
	{
		len = 0;
                while (line[i][len] != 'P' && line[i][len])
			len ++;
		if (line[i][len] == 'P')
			break;
	}
	init(&gui, line, i, len);
	game_loop(&gui);
	free_matrix(line);
	return (0);
}
