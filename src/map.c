/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nino <nino@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:53:15 by nino              #+#    #+#             */
/*   Updated: 2021/11/09 17:39:19 by nino             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	**add_str_map(char **map, char *str)
{
	int		n_str;
	char	**new_map;

	n_str = 0;
	while (map[n_str])
		n_str++;
	n_str++;
	new_map = (char **)malloc(sizeof(char *) * (n_str + 1));
	if (!new_map)
	{
		n_str = 0;
		while (map[n_str])
			free(map[n_str++]);
		free(str);
		get_next_line(-1);
		free(map);
		return ((char **) NULL);
	}
	new_map[n_str--] = NULL;
	new_map[n_str] = str;
	while (n_str--)
		new_map[n_str] = map[n_str];
	free(map);
	return (new_map);
}

char	**get_map(const char *map_file)
{
	int		fd;
	char	**map;
	char	*str;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return ((char **) NULL);
	map = (char **)malloc(sizeof(char *) * 1);
	if (!map)
		return ((char **) NULL);
	map[0] = NULL;
	str = get_next_line(fd);
	while (str)
	{
		map = add_str_map(map, str);
		if (!map)
			return ((char **) NULL);
		str = get_next_line(fd);
	}
	return (map);
}
