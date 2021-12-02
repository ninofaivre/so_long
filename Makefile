# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/09 21:06:19 by nino              #+#    #+#              #
#    Updated: 2021/12/01 00:03:16 by nfaivre          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL = all

NAME = so_long

CC = clang
CFLAGS = -Wall -Werror -Wextra

DIR_SRC = src
DIR_OBJ = .obj

INCLUDE = -Iinclude -Imlx_linux

SRC = $(wildcard $(DIR_SRC)/*.c)
OBJ = $(addprefix $(DIR_OBJ)/, $(notdir $(SRC:.c=.o)))
GNL_OBJ = $(DIR_OBJ)/get_next_line*

mkdir_DIR_OBJ:
	mkdir -p $(DIR_OBJ)

$(DIR_OBJ)/%.o : $(DIR_SRC)/%.c ./include/header.h
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

$(NAME):
	make -C mlx_linux
	make -C Get-Next-Line DIR_OBJ=$(addprefix $(PWD)/, $(DIR_OBJ))
	$(CC) $(CFLAGS) $(OBJ) $(GNL_OBJ) -o $(NAME) -Lmlx_linux -lmlx_Linux -lXext -lX11

all: mkdir_DIR_OBJ $(OBJ) $(NAME)

bonus: all

clean:
	make $@ -C mlx_linux
	make $@ -C Get-Next-Line DIR_OBJ=$(addprefix $(PWD)/, $(DIR_OBJ))
	rm -f $(OBJ)

fclean: clean
	make $@ -C Get-Next-Line DIR_OBJ=$(addprefix $(PWD)/, $(DIR_OBJ))
	rm -f $(NAME)
	rm -rf $(DIR_OBJ)

re: fclean all

.PHONY: all bonus clean fclean re
