#include "../header.h"

void	move_player(t_gui *gui, int y, int x)
{
	int	i;
	
	i = -1;
	if(gui->map[gui->p_y + y][gui->p_x + x] != '1')
	{
		gui->map[gui->p_y][gui->p_x] = '0';
		gui->map[gui->p_y + y][gui->p_x + x] = 'P';
		gui->p_y = gui->p_y + y;
		gui->p_x = gui->p_x + x;		
	}
	while (gui->map[++i])
		ft_printf("%s\n", gui->map[i]);
	return ;
}

int	close_game(int key_code, t_gui *gui)
{
	if(key_code == XK_Escape)
		mlx_destroy_window(gui->mlx, gui->win);
	if (key_code == XK_Right)
		move_player(gui, 0, 1);
	if (key_code == XK_Left)
		move_player(gui, 0, -1);
	if (key_code == XK_Up)
		move_player(gui, -1, 0);
	if (key_code == XK_Down)
		move_player(gui, 1, 0);
	return (0);
}

void	game_loop(char **map, int y, int x)
{
	t_gui	gui;

	gui.mlx = mlx_init();
	gui.map = map;
	gui.p_x = x;
	gui.p_y = y;
	gui.win = mlx_new_window(gui.mlx, 360, 120, "Hello");
	mlx_hook(gui.win, 3, (1L<<1), close_game, &gui);
	mlx_loop(gui.mlx);

	return;
}
