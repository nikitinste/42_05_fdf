# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uhand <uhand@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/31 19:43:18 by uhand             #+#    #+#              #
#    Updated: 2019/02/08 20:51:31 by uhand            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

HEAD = fdf.h
SRC = fdf.c aux_fnctns.c window_control.c
OBJ = fdf.o aux_fnctns.o window_control.o
FLAGS = -g -Wall -Wextra -Werror
LIB = -L libft -lft
LIBPATH = ./libft
#MLIBX = -L  minilibx -lmlx -framework OpenGL -framework AppKit
#MLIBXPATH = ./minilibx

all: $(NAME)

$(NAME): $(OBJ) Makefile
	@make -C $(LIBPATH)
	#@make -C $(MLIBXPATH)
	gcc $(FLAGS) $(OBJ) -o $(NAME) $(LIB) # $(MLIBX)

%.o: %.c $(HEAD)
	gcc $(FLAGS) -c $< -o $@

clean:
	@make -C $(LIBPATH) clean
	#@make -C $(MLIBXPATH) clean
	/bin/rm -f $(OBJ)

fclean: clean
	@make -C $(LIBPATH) fclean
	#@make -C $(MLIBXPATH) fclean
	/bin/rm -f $(NAME)

re: fclean all
