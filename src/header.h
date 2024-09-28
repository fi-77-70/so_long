/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:19:55 by filferna          #+#    #+#             */
/*   Updated: 2024/09/28 14:32:07 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "../libs/libft/libft.h"
# include "../libs/ft_printf/ft_printf.h"
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		llen;
	int		endian;
}	t_img;

typedef struct s_gui
{
	void	*mlx;
	void	*win;
	char	**map;
	int		p_x;
	int		p_y;
	int		map_y;
	int		map_x;
	int		collectables;
	int		moves;
	int		player_c;
	t_img	player;
	t_img	chest;
	t_img	cave;
	t_img	floor;
	t_img	wall;
	t_img	bg;
	t_img	buffer;
}	t_gui;

void	free_gui(t_gui *gui);
void	init(t_gui *gui, char **map);
int		check_map(char **map);
void	free_matrix(char **line);
int		game_loop(t_gui *gui);
int		close_game(int key_code, t_gui *gui);
void	move_player(t_gui *gui, int y, int x);
void	graphics(t_gui *gui);
void	make_map(t_gui *gui);
int		check_numbers(char **map);
int		check_letters(char **map);
void	dup_arr_2(char **dup, char **map);
char	**dup_arr(char **map);
int		really_close(t_gui *gui);
void	put_tiles(t_img *buffer, t_img *tile, int y, int x);
int		confirm_imgs(void);
char	*file_name(char *name);

#endif
