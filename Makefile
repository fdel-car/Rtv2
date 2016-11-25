# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/28 17:56:29 by fdel-car          #+#    #+#              #
#    Updated: 2016/11/25 14:57:25 by fdel-car         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv2

SRCS =  src/color.c src/elems.init.c src/main.c src/parse.elems.c \
		src/push.elems.c src/parse.file.c src/parse.utils.c src/print.elems.c \
		src/vector.c src/vector2.c src/vector3.c src/intersect.c \
		src/raytracing.c src/get_norm.c src/render.ray.c src/key_event.c \
		src/preview.c src/signals.c src/parse.obj.c src/math_tools.c \
		src/load_tex.c src/render.texture.c src/normal.mapping.c

OBJS =	color.o elems.init.o main.o parse.elems.o push.elems.o parse.file.o \
		parse.utils.o print.elems.o vector.o vector2.o vector3.o intersect.o \
		raytracing.o get_norm.o render.ray.o key_event.o preview.o signals.o \
		gtk.o parse.obj.o math_tools.o load_tex.o render.texture.o \
		normal.mapping.o

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
	@cd ressources && mv interface.gtk gtk.c && cd ..
	@clang $(CFLAGS) -c $^ ressources/gtk.c `pkg-config --cflags gtk+-3.0` \
	-I./libft/includes -I./includes
	@cd ressources && mv gtk.c interface.gtk && cd ..

clean:
	@cd libft && make clean && cd ..
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re
