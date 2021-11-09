# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nino <nino@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/09 21:06:19 by nino              #+#    #+#              #
#    Updated: 2021/11/09 21:06:52 by nino             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	clang -Werror -Wextra -Wall *.c ./Get\ Next\ Line/*.c -o so_long ./mlx_linux/libmlx_Linux.a -L/usr/lib -I./Get\ Next\ Line -Imlx_linux -lXext -lX11
