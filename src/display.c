/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nino <nino@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:53:17 by nino              #+#    #+#             */
/*   Updated: 2021/11/11 16:08:58 by nino             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	mlx_int_put(t_vars *vars)
{
	int		nbr_cpy;
	int		nbr_len;
	char	*str;

	nbr_cpy = vars->integers.mooves;
	nbr_len = 0;
	while (nbr_cpy && ++nbr_len)
		nbr_cpy /= 10;
	if (nbr_cpy % 10)
		nbr_len++;
	str = (char *)malloc(sizeof(char) * nbr_len + 1);
	if (str)
	{
		str[nbr_len] = '\0';
		nbr_cpy = vars->integers.mooves;
		while (nbr_len--)
		{
			str[nbr_len] = (nbr_cpy % 10) + 48;
			nbr_cpy /= 10;
		}
		mlx_string_put(vars->mlx, vars->win, 6, 12, 255, str);
		free(str);
	}
}

static void	*player_direction(t_vars *vars)
{
	if (vars->integers.player_last_moove == 119)
		return (vars->img.player_b.img);
	else if (vars->integers.player_last_moove == 97)
		return (vars->img.player_l.img);
	else if (vars->integers.player_last_moove == 100)
		return (vars->img.player_r.img);
	else
		return (vars->img.player_f.img);
}

static void	put_map_char_window(t_vars *vars, int x, int y)
{
	void	*ptr_img;

	if (vars->map[y][x] == '1')
		ptr_img = vars->img.wall.img;
	else if (vars->map[y][x] == 'C')
		ptr_img = vars->img.collectible.img;
	else if (vars->map[y][x] == 'E')
	{
		if (!vars->integers.collectibles)
			ptr_img = vars->img.exit_open.img;
		else
			ptr_img = vars->img.exit.img;
	}
	else if (vars->map[y][x] == 'P')
		ptr_img = player_direction(vars);
	else if (vars->map[y][x] == 'M')
	{
		if (!vars->mob->dir)
			ptr_img = vars->img.mob_l.img;
		else
			ptr_img = vars->img.mob_r.img;
	}
	else
		ptr_img = vars->img.floor.img;
	mlx_put_image_to_window(vars->mlx, vars->win, ptr_img, (x * 32), (y * 32));
}

void	update_map_window(t_vars *vars, int keycode)
{
	put_map_char_window(vars, 0, 0);
	mlx_int_put(vars);
	if (!vars->integers.collectibles)
		put_map_char_window(vars, locate_char(vars->map, 'E', 'x', 1),
			locate_char(vars->map, 'E', 'y', 1));
	put_map_char_window(vars, vars->integers.p_x, vars->integers.p_y);
	put_map_char_window(vars,
		(vars->integers.p_x - (keycode == 100) + (keycode == 97)),
		(vars->integers.p_y - (keycode == 115) + (keycode == 119)));
	while (vars->mob)
	{
		put_map_char_window(vars, vars->mob->x, vars->mob->y);
		put_map_char_window(vars, (vars->mob->x - (vars->mob->dir)
				+ (!vars->mob->dir)), vars->mob->y);
		vars->mob = vars->mob->next;
	}
	vars->mob = vars->ptr_mob;
}

void	put_map_window(t_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	while (vars->map[y])
	{
		x = 0;
		while (vars->map[y][x] != '\n')
		{
			put_map_char_window(vars, x, y);
			x++;
		}
		y++;
	}
}
