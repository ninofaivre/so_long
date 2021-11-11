# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nino <nino@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/10 17:09:05 by nino              #+#    #+#              #
#    Updated: 2021/11/11 16:51:41 by nino             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL = all

CC = clang
CFLAGS = -Wall -Werror -Wextra

DIR_SRC = src
DIR_OBJ ?= .obj

INCLUDE = -Iinclude

SRC = $(wildcard src/*.c)
OBJ = $(addprefix $(DIR_OBJ)/, $(subst src/,, $(SRC:.c=.o)))

$(DIR_OBJ)/%.o : $(DIR_SRC)/%.c ./include/get_next_line.h
	@mkdir -p $(DIR_OBJ)
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

all: $(OBJ) $(SRC)

clean:
	@rm -rf $(OBJ)
	@echo "removing $(OBJ)"

re: clean all

.PHONY: all clean re
