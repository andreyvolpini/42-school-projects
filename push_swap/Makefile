NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR 	= libft
SRC_DIR	= srcs
OPS_DIR 	= $(SRC_DIR)/algo/ops
PARSING_DIR = $(SRC_DIR)/parsing
ALGO_DIR 	= $(SRC_DIR)/algo

LIBFT_SRCS 		= $(wildcard $(LIBFT_DIR)/*.c)
OPS_SRCS 		= $(wildcard $(OPS_DIR)/*.c)
PARSING_SRCS 	= $(wildcard $(PARSING_DIR)/*.c)
ALGO_SRCS 		= $(wildcard $(ALGO_DIR)/*.c)
MAIN_SRCS 		= $(SRC_DIR)/main.c

LIBFT_OBJS 		= $(LIBFT_SRCS:.c=.o) 
OPS_OBJS 		= $(OPS_SRCS:.c=.o) 
PARSING_OBJS 	= $(PARSING_SRCS:.c=.o) 
ALGO_OBJS 		= $(ALGO_SRCS:.c=.o)
MAIN_OBJS 		= $(MAIN_SRCS:.c=.o)

OBJS 			= $(LIBFT_OBJS) $(OPS_OBJS) $(PARSING_OBJS) $(ALGO_OBJS) $(MAIN_OBJS)

INCLUDES = -I. -I$(LIBFT_DIR) -I$(PARSING_DIR) -I$(ALGO_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
