# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uhand <uhand@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/31 19:43:18 by uhand             #+#    #+#              #
#    Updated: 2019/02/26 18:05:34 by uhand            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

HEAD = fdf.h
SRC = fdf.c aux_fnctns.c window_control.c test_fnctns.c line_builder.c \
line_builder_2.c handle_events.c draw_image.c aux_fnctns_2.c
OBJ = fdf.o aux_fnctns.o window_control.o test_fnctns.o line_builder.o \
line_builder_2.o handle_events.o draw_image.o aux_fnctns_2.o
FLAGS = -g -Wall -Wextra -Werror -fsanitize=address
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
