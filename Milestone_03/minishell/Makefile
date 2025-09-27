NAME = minishell

CC = cc
ICLDS = -Iincludes -Ilibft
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
VAL_RULES = --leak-check=full --show-leak-kinds=all --suppressions=readline.supp
#--trace-children=yes

SRCS = \
	srcs/minishell.c \
	srcs/minishell_utils.c \
	srcs/validate_syntax.c \
	srcs/parser/scanner.c \
	srcs/parser/strip_quotes.c \
	srcs/parser/normalize.c \
	srcs/parser/expand.c \
	srcs/parser/expand_utils.c \
	srcs/parser/token_list.c \
	srcs/parser/token_utils.c \
	srcs/parser/tokenize.c \
	srcs/parser/quote.c \
	srcs/execution/execution.c \
	srcs/execution/execution_utils.c \
	srcs/execution/run_builtin.c \
	srcs/execution/pipes.c \
	srcs/execution/create_cmds.c \
	srcs/execution/erro.c \
	srcs/builtins/echo.c \
	srcs/builtins/env.c \
	srcs/builtins/exit.c \
	srcs/builtins/exit_utils.c \
	srcs/builtins/pwd.c \
	srcs/builtins/cd.c \
	srcs/builtins/export.c \
	srcs/builtins/export_utils.c \
	srcs/builtins/export_env.c \
	srcs/builtins/export_create.c \
	srcs/builtins/env_utils.c \
	srcs/builtins/unset.c \
	srcs/redirections/init_opers.c \
	srcs/redirections/heredoc.c \
	srcs/redirections/redirections.c \
	srcs/redirections/redirections_utils.c

BUILD_DIR = build
OBJS = $(SRCS:srcs/%.c=$(BUILD_DIR)/%.o)

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

all: $(LIBFT_A) $(NAME)

$(BUILD_DIR)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	$(CC) $(ICLDS) $(CFLAGS) -c $< -o $@

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_A) -lreadline


valgrind: all
	valgrind $(VAL_RULES) ./$(NAME)

clean:
	rm -rf $(BUILD_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re valgrind
