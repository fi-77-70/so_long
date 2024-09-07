#include "../header.h"

void	move_player(t_gui *gui, int y, int x)
{
	int	i;
	
	i = -1;
	if(gui->map[gui->p_y + y][gui->p_x + x] != '1')
	{
		gui->p_y = gui->p_y + y;
		gui->p_x = gui->p_x + x;		
	}
	while (gui->map[++i])
		ft_printf("%s\n", gui->map[i]);
	return ;
}

int	close_game(int key_code, t_gui *gui)
{
	t_img   floor;
        t_img   wall;
        t_img   player;
	t_img	chest;
	t_img	cave;
        int     wid;
        int     hei;
	
	if(key_code == XK_Escape)
		return (mlx_destroy_window(gui->mlx, gui->win), free_matrix(gui->map), exit(1), 0);
	chest.img = mlx_xpm_file_to_image(gui->mlx, "../imgs/chest.xpm", &wid, &hei);
        chest.addr = mlx_get_data_addr(chest.img, &chest.bits_p_pixel, &chest.line_len, &chest.endian);
        floor.img = mlx_xpm_file_to_image(gui->mlx, "../imgs/floor.xpm", &wid, &hei);
        floor.addr = mlx_get_data_addr(floor.img, &floor.bits_p_pixel, &floor.line_len, &floor.endian);
	cave.img = mlx_xpm_file_to_image(gui->mlx, "../imgs/cave.xpm", &wid, &hei);
        cave.addr = mlx_get_data_addr(cave.img, &cave.bits_p_pixel, &cave.line_len, &cave.endian);
        wall.img = mlx_xpm_file_to_image(gui->mlx, "../imgs/wall.xpm", &wid, &hei);
        wall.addr = mlx_get_data_addr(wall.img, &wall.bits_p_pixel, &wall.line_len, &wall.endian);
        player.img = mlx_xpm_file_to_image(gui->mlx, "../imgs/wizard.xpm", &wid, &hei);
        player.addr = mlx_get_data_addr(player.img, &player.bits_p_pixel, &player.line_len, &player.endian);
	if (key_code == XK_Right)
		move_player(gui, 0, 1);
	if (key_code == XK_Left)
		move_player(gui, 0, -1);
	if (key_code == XK_Up)
		move_player(gui, -1, 0);
	if (key_code == XK_Down)
		move_player(gui, 1, 0);
	graphics(gui, &floor, &wall, &player, &chest, &cave);
	mlx_destroy_image(gui->mlx, player.img);
	mlx_destroy_image(gui->mlx, wall.img);
	mlx_destroy_image(gui->mlx, floor.img);
	mlx_destroy_image(gui->mlx, chest.img);
	mlx_destroy_image(gui->mlx, cave.img);
	return (0);
}

void	put_tiles(t_img *buffer, t_img *tile, int y, int x)
{
	char	*dst;
	char	*src;
	int	a;
	int	b;
	int	temp;

	temp = x;
	a = 0;
	b = 0;
	while(a < 32)
	{
		if (b == 32)
		{
			a++;
			y++;
			b = 0;
			x = temp;
		}
		if(a == 32)
			break;
		dst = buffer->addr + (y * buffer->line_len  + x * (buffer->bits_p_pixel / 8));
                src = tile->addr + (a * tile->line_len + b * (tile->bits_p_pixel / 8));
		if(*src)
			*(unsigned int*)dst = *(unsigned int*)src;
		b++;
		x++;
	}
}

void	graphics(t_gui *gui, t_img *floor, t_img *wall, t_img *player, t_img *chest, t_img *cave)
{
	int	y;
	int	x;
	t_img	buffer;

	y = -1;
	buffer.img = mlx_new_image(gui->mlx, 864, 320);
	buffer.addr = mlx_get_data_addr(buffer.img, &buffer.bits_p_pixel, &buffer.line_len, &buffer.endian);
	while(gui->map[++y])
	{
		x = -1;
		while(gui->map[y][++x])
		{
			if (gui->map[y][x] == '0' || gui->map[y][x] == 'C' || gui->map[y][x] == 'E' || gui->map[y][x] == 'P')
				put_tiles(&buffer, floor, y * 32, x * 32);
			if (gui->map[y][x] == '1')
                                put_tiles(&buffer, wall, y * 32, x * 32);
			if (gui->map[y][x] == 'C')
				put_tiles(&buffer, chest, y * 32, x * 32);
			if (gui->map[y][x] == 'E')
				put_tiles(&buffer, cave, y * 32, x * 32);
			put_tiles(&buffer, player, (gui->p_y * 32), (gui->p_x *32));
		}
	}
	mlx_put_image_to_window(gui->mlx, gui->win, buffer.img, 0, 0);
	mlx_destroy_image(gui->mlx, buffer.img);
}

int	game_loop(char **map, int y, int x)
{
	t_gui	gui;

	gui.mlx = mlx_init();
	gui.map = map;
	gui.p_x = x;
	gui.p_y = y;
	gui.win = mlx_new_window(gui.mlx, 864, 320, "Hello");
	mlx_hook(gui.win, 3, (1L<<1), close_game, &gui);
	mlx_loop(gui.mlx);
	return(0);
}
