# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prastoin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/07 11:13:09 by prastoin          #+#    #+#              #
#    Updated: 2019/01/23 11:21:32 by prastoin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRC = main.c getinfo.c fractol.c initial.c tools.c

OBJ = $(SRC:.c=.o)

FLAG = -Wall -Wextra -Werror -Ofast

LIB = libft/libft.a

LIB2 = -L/usr/local/lib

HEAD = frac.h

LIBX = -lmlx -framework OpenGL -framework AppKit

INC = -I./libft/ -I/usr/local/include

all: $(NAME)

$(NAME): $(OBJ) $(LIB) $(HEAD)
		gcc $(FLAG) $(LIB) $(LIB2) $(INC) $(OBJ) $(LIBX) -o $(NAME)

$(LIB):
		make -C libft/ fclean
			make -C ./libft/

%.o: %.c frac.h
		gcc $(FLAG) $(INC) -o $@ -c $<

clean:
		make -C libft/ clean
			rm -rf $(OBJ)

fclean: clean
		make -C libft/ fclean
			rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all
