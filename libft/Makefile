NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror 

SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_toupper.c ft_tolower.c ft_memset.c ft_bzero.c \
	ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
	ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_strtrim.c ft_split.c ft_strmapi.c \
	ft_itoa.c ft_putendl_fd.c ft_putnbr_fd.c ft_striteri.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "✅ Biblioteca $(NAME) criada com sucesso!"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "🔨 Compilando $<"

clean:
	@rm -f $(OBJ)
	@echo "🗑️ Arquivos .o removidos!"

fclean: clean
	@rm -f $(NAME)
	@echo "🗑️ Tudo limpo, incluindo $(NAME)!"

re: fclean all

bonus:
	@$(MAKE) BONUS=1
	@echo "✨ Funções bônus incluídas!"
