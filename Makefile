# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdel-car <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/28 17:56:29 by fdel-car          #+#    #+#              #
#    Updated: 2016/08/28 17:56:31 by fdel-car         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv2

SRCS = main.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

GTK = `pkg-config --libs gtk+-3.0`

all: $(NAME)

$(NAME): $(OBJS)
	@cd libft && make re && cd ..
	@clang $(GTK) -o $@ $^ ./libft/libft.a
	@echo "\033[1;31mRT compiled successfully"
	@echo "\033[1A\033[0;39m"

$(OBJS): $(SRCS)
	@clang $(CFLAGS) -c $^ `pkg-config --cflags gtk+-3.0` -I./libft/includes

clean:
	@cd libft && make clean && cd ..
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re
