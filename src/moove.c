/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nino <nino@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:17:33 by nino              #+#    #+#             */
/*   Updated: 2021/11/11 16:09:28 by nino             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	next_player_char(int keycode, t_vars *vars)
{
	return (vars->map[vars->integers.p_y - (keycode == 119)
			+ (keycode == 115)][vars->integers.p_x - (keycode == 97)
		+ (keycode == 100)]);
}

static char	next_mob_char(t_vars *vars)
{
	return (vars->map[vars->mob->y][vars->mob->x + (vars->mob->dir)
		- (!vars->mob->dir)]);
}

static void	moove_player(int keycode, t_vars *vars)
{
	vars->map[vars->integers.p_y][vars->integers.p_x] = '0';
	vars->integers.p_x += (keycode == 100) - (keycode == 97);
	vars->integers.p_y += (keycode == 115) - (keycode == 119);
	vars->map[vars->integers.p_y][vars->integers.p_x] = 'P';
}

static void	moove_mob(t_vars *vars)
{
	while (vars->mob)
	{
		if (next_mob_char(vars) == 'P')
		{
			vars->integers.status = -1;
			return ;
		}
		else if (next_mob_char(vars) == '0')
		{
			vars->map[vars->mob->y][vars->mob->x] = '0';
			vars->mob->x += (vars->mob->dir) - (!vars->mob->dir);
			vars->map[vars->mob->y][vars->mob->x] = 'M';
		}
		else
			vars->mob->dir += (!vars->mob->dir) - (vars->mob->dir);
		vars->mob = vars->mob->next;
	}
	vars->mob = vars->ptr_mob;
}

void	moove(int keycode, t_vars *vars)
{
	if (next_player_char(keycode, vars) == 'M')
	{
		vars->integers.status = -1;
		return ;
	}
	else if (next_player_char(keycode, vars) == '1')
		return ;
	else if (next_player_char(keycode, vars) == 'E')
	{
		if (!vars->integers.collectibles)
			vars->integers.status = 1;
		return ;
	}
	else if (next_player_char(keycode, vars) == 'C')
		vars->integers.collectibles--;
	vars->integers.mooves++;
	moove_player(keycode, vars);
	moove_mob(vars);
}
