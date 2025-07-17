NAME       := pipex
CC         := cc
CFLAGS     := -Wall -Wextra -Werror

INCLUDES   := -Iincludes -Ilibft

SRC_DIR    := srcs
LIBFT_DIR  := libft

SRC_FILES   := $(wildcard $(SRC_DIR)/*.c)
LIBFT_FILES := $(wildcard $(LIBFT_DIR)/*.c)

SRC_OBJS    := $(SRC_FILES:%.c=%.o)
LIBFT_OBJS  := $(LIBFT_FILES:%.c=%.o)
OBJS        := $(SRC_OBJS) $(LIBFT_OBJS)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_DIR)/%.o: $(LIBFT_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
