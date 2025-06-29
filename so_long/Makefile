NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = mlx

SRCS = gnl/get_next_line.c \
	map/map_loader.c map/map_validator.c map/flood_fill.c \
	srcs/load_images.c srcs/render_map.c \
	srcs/init_game.c srcs/controls.c srcs/main.c \
	libft/ft_putchar_fd.c libft/ft_putnbr_fd.c \
	libft/ft_putstr_fd.c libft/ft_strdup.c \
	libft/ft_strncmp.c libft/ft_strlen.c libft/ft_strchr.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -Imlx -I. -Ilibft $(OBJS) -Lmlx -lmlx -lXext -lX11 -lm -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
//.SILENT:
