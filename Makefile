# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uhand <uhand@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/31 19:43:18 by uhand             #+#    #+#              #
#    Updated: 2019/03/17 14:45:45 by uhand            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

HEAD = fdf.h
SRC = fdf.c aux_fnctns.c window_control.c line_builder.c \
line_builder_2.c handle_events.c draw_image.c aux_fnctns_2.c handle_events_2.c \
handle_events_3.c draw_image_2.c line_builder_1.c
OBJ = fdf.o aux_fnctns.o window_control.o line_builder.o \
line_builder_2.o handle_events.o draw_image.o aux_fnctns_2.o handle_events_2.o \
handle_events_3.o draw_image_2.o line_builder_1.o
FLAGS = -Wall -Wextra -Werror -g -m64 -Ofast -flto -march=native -funroll-loops -fsanitize=address
LIB = -L libft -lft
LIBPATH = ./libft
MLIBX = -L  minilibx -lmlx -framework OpenGL -framework AppKit
MLIBXPATH = ./minilibx

all: $(NAME)

$(NAME): $(OBJ) Makefile
	@make -C $(LIBPATH)
	@make -C $(MLIBXPATH)
	gcc $(FLAGS) $(OBJ) -o $(NAME) $(LIB) $(MLIBX)

%.o: %.c $(HEAD)
	gcc $(FLAGS) -c $< -o $@

clean:
	@make -C $(LIBPATH) clean
	@make -C $(MLIBXPATH) clean
	/bin/rm -f $(OBJ)

fclean: clean
	@make -C $(LIBPATH) fclean
	@make -C $(MLIBXPATH) fclean
	/bin/rm -f $(NAME)

re: fclean all
