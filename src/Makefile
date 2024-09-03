NAME = test

SRC = test.c ./parsers/map_checker.c ./logic/game_logic.c

LIBFT = ../libs/libft

PRINTF = ../libs/ft_printf

MLX = 

API = -L../minilibx-linux -lmlx -L~/../../usr/local/lib -lXext -lX11 -lm -lbsd

LIBS = ../libs/libft/libft.a ../libs/ft_printf/libftprintf.a

all: $(NAME)

$(NAME): $(SRC) $(LIBS)
	cc -Wall -Werror -Wextra $(SRC) $(LIBS) $(API) -g -o $(NAME)

$(LIBS): $(LIBFT) $(PRINTF) $(MLX_O)
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(PRINTF)


re: fclean all

clean:
	$(MAKE) clean -C $(LIBFT)
	$(MAKE) clean -C $(PRINTF)

fclean: clean
	$(MAKE) fclean -C $(LIBFT)
	$(MAKE) fclean -C $(PRINTF)
	rm test
