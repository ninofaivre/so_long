/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nino <nino@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:38:50 by nino              #+#    #+#             */
/*   Updated: 2021/11/09 21:01:08 by nino             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	size_map(char **map, char width_or_height)
{
	int	width;
	int	height;

	width = 0;
	height = 0;
	while (map[height])
	{
		while (map[height][width])
			width++;
		height++;
	}
	return ((height * (width_or_height == 'h') * 32)
		+ ((width - 1) * (width_or_height == 'w') * 32));
}

int	locate_char(char **map, char c, char x_or_y, int occur)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == c)
				occur--;
			if (!occur)
				break ;
			x++;
		}
		if (!occur)
			break ;
		y++;
	}
	if (!map[y])
		return (-1);
	return (((x_or_y == 'x') * x) + ((x_or_y == 'y') * y));
}

static void	load_img(t_vars *vars)
{
	load_asset(vars, "asset/collectible.xpm", &vars->img.collectible);
	load_asset(vars, "asset/exit.xpm", &vars->img.exit);
	load_asset(vars, "asset/exit_open.xpm", &vars->img.exit_open);
	load_asset(vars, "asset/mob_l.xpm", &vars->img.mob_l);
	load_asset(vars, "asset/mob_r.xpm", &vars->img.mob_r);
	load_asset(vars, "asset/player_b.xpm", &vars->img.player_b);
	load_asset(vars, "asset/player_f.xpm", &vars->img.player_f);
	load_asset(vars, "asset/player_r.xpm", &vars->img.player_r);
	load_asset(vars, "asset/player_l.xpm", &vars->img.player_l);
	load_asset(vars, "asset/floor.xpm", &vars->img.floor);
	load_asset(vars, "asset/wall.xpm", &vars->img.wall);
	load_asset(vars, "asset/win.xpm", &vars->img.win);
	load_asset(vars, "asset/loose.xpm", &vars->img.loose);
}

t_mob	*init_mob(t_vars *vars)
{
	t_mob	*mob;
	int		i;

	mob = NULL;
	i = 1;
	if (!(locate_char(vars->map, 'M', 'x', i) == -1))
		mob = (t_mob *)malloc(sizeof(t_mob));
	if (!(locate_char(vars->map, 'M', 'x', i) == -1) && !mob)
		return ((t_mob *) -1);
	vars->ptr_mob = mob;
	while (!(locate_char(vars->map, 'M', 'x', i) == -1))
	{
		mob->x = locate_char(vars->map, 'M', 'x', i);
		mob->y = locate_char(vars->map, 'M', 'y', i);
		mob->dir = 0;
		i++;
		mob->next = NULL;
		if (!(locate_char(vars->map, 'M', 'x', i) == -1))
			mob->next = (t_mob *)malloc(sizeof(t_mob));
		if (!(locate_char(vars->map, 'M', 'x', i) == -1) && !mob->next)
			return (free_mob(vars));
		mob = mob->next;
	}
	return (vars->ptr_mob);
}

int	init(t_vars *vars, char *map_file)
{
	int	i;

	i = 0;
	vars->map = get_map(map_file);
	if (!vars->map)
		return (-1);
	vars->mob = init_mob(vars);
	if (vars->mob == ((t_mob *) -1))
	{
		while (vars->map[i])
			free(vars->map[i++]);
		free(vars->map);
		return (-1);
	}
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, size_map(vars->map, 'w'),
			size_map(vars->map, 'h'), "so_long");
	vars->integers.p_x = locate_char(vars->map, 'P', 'x', 1);
	vars->integers.p_y = locate_char(vars->map, 'P', 'y', 1);
	vars->integers.collectibles = 1;
	vars->integers.mooves = 0;
	vars->integers.player_last_moove = 0;
	vars->integers.status = 0;
	load_img(vars);
	return (0);
}
