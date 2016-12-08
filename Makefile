# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/28 17:56:29 by fdel-car          #+#    #+#              #
#    Updated: 2016/12/08 12:25:31 by bhuver           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv2

SRCS =  src/color.c src/elems.init.c src/main.c src/parse.elems.c \
		src/push.elems.c src/parse.file.c src/parse.utils.c \
		src/vector.c src/vector2.c src/vector3.c src/intersect.c \
		src/raytracing.c src/get_norm.c src/render.ray.c src/key_event.c \
		src/preview.c src/signals.c src/parse.obj.c src/math_tools.c \
		src/load_tex.c src/render.texture.c src/normal.mapping.c \
		src/parse.obj2.c src/preview2.c src/render.ray2.c \
		src/gtk.c src/render.texture2.c src/complex_objects.c \
		src/intersect2.c src/post_process.c src/post_process2.c \
		src/parse.utils2.c src/shadow.c src/stereoscopie.c

OBJS =	color.o elems.init.o main.o parse.elems.o push.elems.o parse.file.o \
		parse.utils.o vector.o vector2.o vector3.o intersect.o raytracing.o \
		get_norm.o render.ray.o key_event.o preview.o signals.o gtk.o \
		parse.obj.o parse.obj2.o math_tools.o load_tex.o preview2.o \
		render.texture.o normal.mapping.o render.ray2.o render.texture2.o \
		complex_objects.o intersect2.o post_process.o post_process2.o\
		parse.utils2.o shadow.o stereoscopie.o

CFLAGS = -Wall -Wextra -Werror

GTK = `pkg-config --libs gtk+-3.0`

all: $(NAME)

$(NAME): $(OBJS)
	# @cd libft && make re && cd ..
	@gcc  -I./includes $(GTK) -o $@ $^ ./libft/libft.a
	@echo "\033[1;31mRT compiled successfully"
	@echo "\033[1A\033[0;39m"
	@rm *.o

$(OBJS): $(SRCS)
	@clang $(CFLAGS) -c $^ `pkg-config --cflags gtk+-3.0` \
	-I./libft/includes -I./includes

clean:
	@cd libft && make clean && cd ..
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re
