#include "../libs/libft/libft.h"
#include "../libs/ft_printf/ft_printf.h"
#include <mlx.h>
#include <X11/keysym.h>
#include <X11/X.h>

#ifndef HEADER_H
#define HEADER_H


typedef struct s_gui{
	void	*mlx;
	void	*win;
	char	**map;
	int	p_x;
	int	p_y;
}	t_gui;

int	check_map(char **map);
void	free_matrix(char **line);
void	game_loop(char **map, int y, int x);

#endif
