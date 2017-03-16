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

SRCS = src/color.c src/elems.init.c src/main.c src/parse.elems.c \
		src/push.elems.c src/parse.file.c src/parse.utils.c \
		src/vector.c src/vector2.c src/vector3.c src/intersect.c \
		src/raytracing.c src/get_norm.c src/render.ray.c src/key_event.c \
		src/preview.c src/signals.c src/parse.obj.c src/math_tools.c \
		src/load_tex.c src/render.texture.c src/normal.mapping.c \
		src/parse.obj2.c src/preview2.c src/render.ray2.c \
	 	src/render.texture2.c src/complex_objects.c src/signals2.c \
		src/intersect2.c src/post_process.c src/post_process2.c \
		src/parse.utils2.c src/shadow.c src/stereoscopie.c src/verif.file.c \
		src/perlin.c src/key_event2.c src/various_func.c src/progress_bar.c\
		src/parse.elems2.c src/free.utils.c src/gtk/gtk.c src/gtk/gtk_f1.c\
		src/gtk/gtk_f2.c src/gtk/gtk_f3.c src/gtk/gtk_f4.c src/gtk/gtk_f5.c\
		src/gtk/gtk_f6.c src/gtk/gtk_f7.c src/gtk/gtk_f8.c src/gtk/gtk_f9.c\
		src/gtk/gtk_f10.c src/gtk/gtk_f11.c src/gtk/gtk_f12.c src/gtk/gtk_f13.c\
		src/gtk/gtk_f14.c src/gtk/gtk_f15.c src/gtk/gtk_f16.c src/gtk/gtk_f17.c\
		src/gtk/gtk_f18.c src/gtk/gtk_f19.c src/gtk/gtk_f20.c src/gtk/gtk_f21.c\
		src/gtk/gtk_f12_1.c src/free_exit.c

OBJS = color.o elems.init.o main.o parse.elems.o push.elems.o parse.file.o \
		parse.utils.o vector.o vector2.o vector3.o intersect.o raytracing.o \
		get_norm.o render.ray.o key_event.o preview.o signals.o gtk.o \
		parse.obj.o parse.obj2.o math_tools.o load_tex.o preview2.o \
		render.texture.o normal.mapping.o render.ray2.o render.texture2.o \
		complex_objects.o intersect2.o post_process.o post_process2.o \
		parse.utils2.o shadow.o stereoscopie.o verif.file.o perlin.o \
		key_event2.o various_func.o progress_bar.o parse.elems2.o\
		free.utils.o gtk_f1.o gtk_f2.o gtk_f3.o gtk_f4.o gtk_f5.o\
		gtk_f6.o gtk_f7.o gtk_f8.o gtk_f9.o gtk_f10.o gtk_f11.o\
		gtk_f12.o gtk_f13.o gtk_f14.o gtk_f15.o gtk_f16.o gtk_f17.o\
		gtk_f18.o gtk_f19.o gtk_f20.o gtk_f21.o signals2.o\
		gtk_f12_1.o free_exit.o

CFLAGS = -Wall -Wextra -Werror

GTK = `pkg-config --libs gtk+-3.0`

all: $(NAME)

$(NAME): $(OBJS)
	@make re -C libft
	@gcc  -I./includes $(GTK) -o $@ $^ ./libft/libft.a
	@echo "\033[1;31m$(NAME) compiled successfully"
	@echo "\033[1A\033[0;39m"
	@rm *.o

$(OBJS): $(SRCS)
	@clang $(CFLAGS) -c $^ `pkg-config --cflags gtk+-3.0` \
	-I./libft/includes -I./includes

clean:
	@make clean -C libft
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re
