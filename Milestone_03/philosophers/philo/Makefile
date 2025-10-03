# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/02 12:43:51 by avolpini          #+#    #+#              #
#    Updated: 2025/10/02 12:43:51 by avolpini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
IFLAGS	= -I include

SRCS	 = \
		srcs/monitor.c \
		srcs/routine.c \
		srcs/threads.c \
		srcs/access.c \
		srcs/state.c \
		srcs/table.c \
		srcs/utils.c \
		srcs/init.c \
		srcs/main.c

OBJS	= $(SRCS:srcs/%.c=build/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)
	@echo "----------- 🍴 PHILO by Andrey 😒 -----------\n"

build/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	@$(RM) -r $(OBJS)
	@echo "--------------- 🧹 CLEAN DONE --------------- \n"

fclean: clean
	@$(RM) -r $(NAME)
	@echo "--------------- 🧹 FCLEAN DONE --------------- \n"

re: fclean all

.PHONY: all clean fclean re