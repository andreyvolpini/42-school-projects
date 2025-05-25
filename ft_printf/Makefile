NAME = libftprintf.a
SRC = ft_formats.c ft_printf.c ft_putchar.c ft_putstr.c \
	ft_putnbr.c ft_putnbr_unsigned.c ft_puthex.c ft_putptr.c
CFLAGS = -Wall -Wextra -Werror
OBJ = $(SRC:.c=.o)
CC = cc
AR = ar rcs
TEST = test_printf.c
TEST_EXEC = test_printf

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

test: $(NAME)
	$(CC) $(CFLAGS) $(TEST) $(NAME) -o $(TEST_EXEC)
	./$(TEST_EXEC)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
