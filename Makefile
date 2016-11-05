# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/28 17:56:29 by fdel-car          #+#    #+#              #
#    Updated: 2016/10/28 12:02:24 by vde-la-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv2

SRCS = $(shell find src -type f -name "*.c")

OBJS =	color.o elems.init.o main.o parse.elems.o push.elems.o parse.file.o \
		parse.utils.o print.elems.o vector.o vector2.o vector3.o intersect.o \
		raytracing.o get_norm.o render.ray.o key_event.o preview.o signals.o

CFLAGS = -Wall -Wextra -Werror

GTK = `pkg-config --libs gtk+-3.0`

all: $(NAME)

$(NAME): $(OBJS)
	# @cd libft && make re && cd ..
	gcc  -I./includes $(GTK) -o $@ $^ ./libft/libft.a
	@echo "\033[1;31mRT compiled successfully"
	@echo "\033[1A\033[0;39m"
	@rm *.o

$(OBJS): $(SRCS)
	@clang $(CFLAGS) -c $^ `pkg-config --cflags gtk+-3.0` -I./libft/includes -I./includes

clean:
	@cd libft && make clean && cd ..
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re
