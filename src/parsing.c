/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nino <nino@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:40:10 by nino              #+#    #+#             */
/*   Updated: 2021/11/11 16:20:48 by nino             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	check_map_name(char *map)
{
	while (*map != '.' && *map)
		map++;
	return (!(*map && *(map + 1) == 'b' && *(map + 2) == 'e'
			&& *(map + 3) == 'r') * (-1));
}

static int	count_map_element(char **map, char element)
{
	int	n_element;
	int	y;
	int	x;

	n_element = 0;
	y = 1;
	x = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == element)
				n_element++;
			x++;
		}
		y++;
	}
	return (n_element);
}

static int	check_map_line(char *line, int map_width)
{
	int	i;

	i = 0;
	if (line[i] != '1')
		return (-1);
	while (line[i])
	{
		if (line[i] != 'M' && line[i] != '0' && line[i] != '1' && line[i] != 'E'
			&& line[i] != 'P' && line[i] != 'C' && line[i] != '\n')
			return (-1);
		i++;
	}
	if (line[i - 1] != '\n' || line[i - 2] != '1' || map_width != i - 1)
		return (-1);
	return (0);
}

static int	check_map(char **map)
{
	int	map_width;
	int	y;
	int	x;

	map_width = 0;
	y = 1;
	x = 0;
	while (map[0][map_width] == '1')
		map_width++;
	if (map[0][map_width] != '\n' || map[0][map_width + 1] != '\0')
		return (-1);
	while (map[y + 1])
	{
		if (check_map_line(map[y], map_width) == -1)
			return (-1);
		y++;
	}
	while (map[y][x] == '1')
		x++;
	if (map[y][x] != '\n' || map[y][x + 1] != '\0' || x != map_width)
		return (-1);
	return (0);
}

int	parsing(t_vars *vars, char *map_file)
{
	if (check_map_name(map_file) == -1)
		return (print_error(2));
	vars->integers.collectibles = count_map_element(vars->map, 'C');
	if (!vars->integers.collectibles)
		return (print_error(3));
	if (count_map_element(vars->map, 'P') != 1)
		return (print_error(4));
	if (count_map_element(vars->map, 'E') != 1)
		return (print_error(5));
	if (check_map(vars->map) == -1)
		return (print_error(6));
	return (0);
}
