/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:31:05 by filferna          #+#    #+#             */
/*   Updated: 2024/09/28 14:40:10 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	close_game(int key_code, t_gui *gui)
{
	if (key_code == XK_Escape)
		return (free_gui(gui), free_matrix(gui->map), exit(1), 0);
	if (key_code == XK_Right)
		move_player(gui, 0, 1);
	if (key_code == XK_Left)
		move_player(gui, 0, -1);
	if (key_code == XK_Up)
		move_player(gui, -1, 0);
	if (key_code == XK_Down)
		move_player(gui, 1, 0);
	graphics(gui);
	if (gui->map[gui->p_y][gui->p_x] == 'E'
		&& gui->collectables == gui->player_c)
		return (free_gui(gui), free_matrix(gui->map), exit(1), 0);
	return (0);
}

void	put_tiles(t_img *buffer, t_img *tile, int y, int x)
{
	char	*dst;
	char	*src;
	int		a;
	int		b;
	int		temp;

	temp = x;
	a = 0;
	b = -1;
	while (a < 32)
	{
		if (++b == 32)
		{
			a++;
			y++;
			b = 0;
			x = temp;
		}
		if (x++ && a == 32)
			break ;
		dst = buffer->addr + (y * buffer->llen + x * (buffer->bpp / 8));
		src = tile->addr + (a * tile->llen + b * (tile->bpp / 8));
		if (*src)
			*(unsigned int *)dst = *(unsigned int *)src;
	}
}

void	put_back_groud(t_img *buffer, t_gui *gui, int y, int x)
{
	int		a;
	int		b;
	char	*dst;
	char	*src;

	a = 0;
	b = 0;
	while (a < 32 * gui->map_y)
	{
		if (b == 32 * gui->map_x)
		{
			a++;
			y++;
			b = 0;
			x = 0;
		}
		if (a == 32 * gui->map_y)
			break ;
		dst = buffer->addr + (y * buffer->llen + x * (buffer->bpp / 8));
		src = gui->bg.addr + (a * gui->bg.llen + b * (gui->bg.bpp / 8));
		if (*src)
			*(unsigned int *)dst = *(unsigned int *)src;
		b++;
		x++;
	}
}

void	graphics(t_gui *gui)
{
	t_img	buffer;

	buffer.img = mlx_new_image(gui->mlx, gui->map_x * 32, gui->map_y * 32);
	buffer.addr = mlx_get_data_addr(buffer.img,
			&buffer.bpp, &buffer.llen, &buffer.endian);
	put_back_groud(&buffer, gui, 0, 0);
	put_tiles(&buffer, &gui->player, (gui->p_y * 32), (gui->p_x * 32));
	mlx_put_image_to_window(gui->mlx, gui->win, buffer.img, 0, 0);
	mlx_destroy_image(gui->mlx, buffer.img);
}

int	game_loop(t_gui *gui)
{
	make_map(gui);
	graphics(gui);
	mlx_hook(gui->win, KeyPress, KeyPressMask, close_game, gui);
	mlx_hook(gui->win, DestroyNotify, NoEventMask, really_close, gui);
	mlx_loop(gui->mlx);
	return (0);
}
