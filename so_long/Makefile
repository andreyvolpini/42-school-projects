NAME    = so_long
CC      = cc
CFLAGS  = -Wall -Wextra -Werror

MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a

SRCS = gnl/get_next_line.c \
       map/map_loader.c map/map_validator.c map/flood_fill.c \
       srcs/load_images.c srcs/render_map.c \
       srcs/init_game.c srcs/controls.c srcs/main.c \
       libft/ft_putchar_fd.c libft/ft_putnbr_fd.c \
       libft/ft_putstr_fd.c libft/ft_strdup.c \
       libft/ft_strncmp.c libft/ft_strlen.c libft/ft_strchr.c

OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@echo "→ Compilando MiniLibX em $(MLX_DIR)…"
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I$(MLX_DIR) -I. -Ilibft \
		$^ \
		-L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm \
		-o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -I. -Ilibft -c $< -o $@

clean:
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(NAME) $(MLX_LIB)

re: fclean all
