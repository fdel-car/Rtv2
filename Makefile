# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/28 17:56:29 by fdel-car          #+#    #+#              #
#    Updated: 2016/12/15 14:37:56 by fdel-car         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv2

SRCS := $(shell echo src/*.c src/gtk/*.c)

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

GTK = `pkg-config --libs gtk+-3.0`

all: $(NAME)

$(NAME): clean lib $(OBJS) # clean not supposed to be here
	@mv gtk*.o src/gtk && mv *.o src
	@gcc -I./includes $(GTK) -o $@ $(OBJS) ./libft/libft.a -lm -pthread # -lm and -pthred could probably be removed on macOs
	@echo "\n\033[2K\033[1;31m$(NAME) compiled successfully\033[0;39m"

%.o: %.c
	@echo "\033[2K\033[1;33mCreating object of the $(NAME) with $^...\033[0;39m\033[1A"
	@gcc $(CFLAGS) -c $^ `pkg-config --cflags gtk+-3.0` \
	-I./libft/includes -I./includes

lib:
	@make -C libft

clean:
	@make clean -C libft
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re
