# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uhand <uhand@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/18 18:04:25 by uhand             #+#    #+#              #
#    Updated: 2019/02/13 17:55:02 by uhand            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

HEAD = libft.h
SRC = ft_putchar.c ft_putchar_fd.c ft_putstr.c ft_putstr_fd.c ft_putendl.c \
ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_strlen.c ft_isalpha.c \
ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
ft_strchr.c ft_strrchr.c ft_strequ.c ft_strnequ.c ft_strstr.c ft_strnstr.c \
ft_strcmp.c ft_strncmp.c ft_atoi.c ft_memalloc.c ft_strnew.c ft_memset.c \
ft_bzero.c ft_strclr.c ft_memchr.c ft_memcmp.c ft_memdel.c ft_strdel.c \
ft_strdup.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_order.c \
ft_itoa.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_memcpy.c \
ft_memccpy.c ft_memmove.c ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c \
ft_strlcat.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c \
ft_lstmap.c ft_lstfree.c ft_lstaddnext.c ft_lstdelfirst.c get_next_line.c \
ft_lstcount.c ft_abs.c
OBJ = ft_putchar.o ft_putchar_fd.o ft_putstr.o ft_putstr_fd.o ft_putendl.o \
ft_putendl_fd.o ft_putnbr.o ft_putnbr_fd.o ft_strlen.o ft_isalpha.o \
ft_isdigit.o ft_isalnum.o ft_isascii.o ft_isprint.o ft_toupper.o ft_tolower.o \
ft_strchr.o ft_strrchr.o ft_strequ.o ft_strnequ.o ft_strstr.o ft_strnstr.o \
ft_strcmp.o ft_strncmp.o ft_atoi.o ft_memalloc.o ft_strnew.o ft_memset.o \
ft_bzero.o ft_strclr.o ft_memchr.o ft_memcmp.o ft_memdel.o ft_strdel.o \
ft_strdup.o ft_strsub.o ft_strjoin.o ft_strtrim.o ft_strsplit.o ft_order.o \
ft_itoa.o ft_striter.o ft_striteri.o ft_strmap.o ft_strmapi.o ft_memcpy.o \
ft_memccpy.o ft_memmove.o ft_strcpy.o ft_strncpy.o ft_strcat.o ft_strncat.o \
ft_strlcat.o ft_lstnew.o ft_lstdelone.o ft_lstdel.o ft_lstadd.o ft_lstiter.o \
ft_lstmap.o ft_lstfree.o ft_lstaddnext.o ft_lstdelfirst.o get_next_line.o \
ft_lstcount.o ft_abs.o
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
	/bin/rm -f libft.h.gch

$(OBJ): $(SRC) $(HEAD)
	gcc -c $(SRC) $(HEAD) $(FLAGS)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
