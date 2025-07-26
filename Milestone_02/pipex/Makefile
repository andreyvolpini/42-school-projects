NAME       	:= pipex
CC         	:= cc
CFLAGS     	:= -Wall -Wextra -Werror

INCLUDES   	:= -Iincludes -Ilibft

SRC_DIR    	:= srcs
LIBFT_DIR  	:= libft
OBJ_DIR		:= .builter

SRC_FILES   := $(wildcard $(SRC_DIR)/*.c)
LIBFT_FILES := $(wildcard $(LIBFT_DIR)/*.c)

SRC_OBJS    := $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(SRC_FILES)))
LIBFT_OBJS  := $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(LIBFT_FILES)))
OBJS        := $(SRC_OBJS) $(LIBFT_OBJS)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(LIBFT_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
