# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uhand <uhand@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/31 19:43:18 by uhand             #+#    #+#              #
#    Updated: 2019/03/26 19:47:19 by uhand            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

HEAD = fdf.h
SRC = fdf.c aux_fnctns.c window_control.c line_builder.c \
line_builder_2.c handle_events.c draw_image.c aux_fnctns_2.c handle_events_2.c \
handle_events_3.c draw_image_2.c line_builder_1.c aux_fnctns_3.c
OBJ = $(addprefix $(OBJPATH)/,$(SRC:.c=.o))
FLAGS = -Wall -Wextra -Werror -m64 -Ofast -flto -march=native -funroll-loops
LIB = -L libft -lft
LIBPATH = ./libft

MLIBX = -L  minilibx -lmlx -framework OpenGL -framework AppKit
MLIBXPATH = ./minilibx
OBJPATH = ./objects

all:
	mkdir -p $(OBJPATH)
	@make $(NAME)

$(OBJPATH)/%.o: %.c $(HEAD)
	gcc $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@make -C $(LIBPATH)
	@make -C $(MLIBXPATH)
	gcc $(OBJ) -o $(NAME) $(LIB) $(MLIBX)

clean:
	@make -C $(LIBPATH) clean
	@make -C $(MLIBXPATH) clean
	/bin/rm -rf $(OBJPATH)

fclean: clean
	@make -C $(LIBPATH) fclean
	@make -C $(MLIBXPATH) fclean
	/bin/rm -f $(NAME)

re: fclean all
