NAME = test

SRC = test.c ./parsers/map_checker.c

LIBFT = ../libs/libft

PRINTF = ../libs/ft_printf

LIBS = ../libs/libft/libft.a ../libs/ft_printf/libftprintf.a

all: $(NAME)

$(NAME): $(SRC) $(LIBS)
	cc -Wall -Werror -Wextra $(SRC) $(LIBS) -g -o test

$(LIBS): $(LIBFT) $(PRINTF)
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
