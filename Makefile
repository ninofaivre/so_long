# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nino <nino@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/09 21:06:19 by nino              #+#    #+#              #
#    Updated: 2021/11/19 10:34:41 by nino             ###   ########.fr        #
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
OBJ = $(addprefix $(DIR_OBJ)/, $(subst src/,, $(SRC:.c=.o)))

GNL:
	@make -C Get-Next-Line DIR_OBJ=$(addprefix $(PWD)/, $(DIR_OBJ))

GNL_OBJ = $(DIR_OBJ)/get_next_line.o $(DIR_OBJ)/get_next_line_utils.o

$(DIR_OBJ)/%.o : $(DIR_SRC)/%.c ./include/header.h
	@mkdir -p $(DIR_OBJ)
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

$(NAME): $(OBJ)
	@make -C mlx_linux
	$(CC) $(CFLAGS) $(OBJ) $(GNL_OBJ) -o $(NAME) -Lmlx_linux -l:libmlx_Linux.a -L/usr/lib -lXext -lX11

all: GNL $(OBJ) $(NAME)

bonus: all

clean:
	@make $@ -C mlx_linux
	@make $@ -C Get-Next-Line DIR_OBJ=$(addprefix $(PWD)/, $(DIR_OBJ))
	@rm -rf $(OBJ)
	@echo "removing $(OBJ)"

fclean: clean
	@rm -rf $(NAME)
	@echo "removing $(NAME)"

re: fclean all

.PHONY: GNL all bonus clean re fclean
