/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nino <nino@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:02:44 by nino              #+#    #+#             */
/*   Updated: 2021/11/11 16:40:55 by nino             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	print_error(int i)
{
	write(2, "Error\n", 6);
	write(2, "======================================================\n", 55);
	if (i == 0)
	{
		write(2, "WRONG ARGS !\nUsage : ./so_long [MAP'S_NAME.ber]\n", 49);
		write(2, "Exemple : ./so_long 'test.ber'\n", 31);
	}
	else if (i == 1)
		write(2, "MALLOC FAILED DURING INIT !\n", 28);
	else if (i == 2)
		write(2, "WRONG MAP'S NAME !\n", 19);
	else if (i == 3)
		write(2, "NO COLLECTIBLE !\n", 17);
	else if (i == 4)
		write(2, "NUMBER OF PLAYER ERROR (1 PLAYER NEEDED) !\n", 43);
	else if (i == 5)
		write(2, "NUMBER OF EXIT ERROR  (1 EXIT NEEDED)!\n", 39);
	else if (i == 6)
	{
		write(2, "MAP ERROR ! (MAP MUST BE SURROUNDED BY WALLS, RECTANGLE", 55);
		write(2, " AND CONTAIN ONLY ['0', '1', 'P', 'C', 'E', 'M']\n", 49);
	}
	write(2, "======================================================\n", 55);
	return (-1);
}

static void	quit(t_vars *vars)
{
	int		i;

	i = 0;
	while (vars->map[i])
		free(vars->map[i++]);
	free(vars->map);
	free_mob(vars);
	mlx_destroy_image(vars->mlx, vars->img.collectible.img);
	mlx_destroy_image(vars->mlx, vars->img.exit_open.img);
	mlx_destroy_image(vars->mlx, vars->img.exit.img);
	mlx_destroy_image(vars->mlx, vars->img.mob_l.img);
	mlx_destroy_image(vars->mlx, vars->img.mob_r.img);
	mlx_destroy_image(vars->mlx, vars->img.player_b.img);
	mlx_destroy_image(vars->mlx, vars->img.player_f.img);
	mlx_destroy_image(vars->mlx, vars->img.player_l.img);
	mlx_destroy_image(vars->mlx, vars->img.player_r.img);
	mlx_destroy_image(vars->mlx, vars->img.floor.img);
	mlx_destroy_image(vars->mlx, vars->img.wall.img);
	mlx_destroy_image(vars->mlx, vars->img.win.img);
	mlx_destroy_image(vars->mlx, vars->img.loose.img);
	mlx_loop_end(vars->mlx);
}

static void	end(t_vars *vars)
{
	mlx_clear_window(vars->mlx, vars->win);
	if (vars->integers.status == 1)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.win.img,
			((size_map(vars->map, 'w') / 2) - (vars->img.win.width / 2)),
			((size_map(vars->map, 'h') / 2) - (vars->img.win.height / 2)));
	else if (vars->integers.status == -1)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.loose.img,
			((size_map(vars->map, 'w') / 2) - (vars->img.loose.width / 2)),
			((size_map(vars->map, 'h') / 2) - (vars->img.loose.height / 2)));
	vars->integers.status = 2;
}

static void	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		quit(vars);
	else if ((keycode == 119 || keycode == 97 || keycode == 115
			|| keycode == 100) && vars->integers.status == 0)
	{
		vars->integers.player_last_moove = keycode;
		moove(keycode, vars);
		update_map_window(vars, keycode);
	}
	if (vars->integers.status == -1 || vars->integers.status == 1)
		end(vars);
}

int	main(int ac, char **av)
{
	t_vars		vars;

	if (ac != 2 || init(&vars, av[1]) == -1)
	{
		print_error((ac == 2));
		exit(EXIT_FAILURE);
	}
	if (parsing(&vars, av[1]) == -1)
	{
		quit(&vars);
		mlx_destroy_window(vars.mlx, vars.win);
		mlx_destroy_display(vars.mlx);
		free(vars.mlx);
		exit(EXIT_FAILURE);
	}
	put_map_window(&vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 17, 1L << 17, quit, &vars);
	mlx_loop(vars.mlx);
	mlx_destroy_window(vars.mlx, vars.win);
	mlx_destroy_display(vars.mlx);
	free(vars.mlx);
	return (EXIT_SUCCESS);
}
