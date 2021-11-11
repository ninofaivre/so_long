/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nino <nino@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:58:38 by nino              #+#    #+#             */
/*   Updated: 2021/11/11 16:32:19 by nino             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_mob
{
	int				x;
	int				y;
	int				dir;
	struct s_mob	*next;
}	t_mob;

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
}	t_img;

typedef struct s_img_list
{
	struct s_img	collectible;
	struct s_img	exit_open;
	struct s_img	exit;
	struct s_img	mob_l;
	struct s_img	mob_r;
	struct s_img	player_b;
	struct s_img	player_f;
	struct s_img	player_l;
	struct s_img	player_r;
	struct s_img	floor;
	struct s_img	wall;
	struct s_img	win;
	struct s_img	loose;
}	t_img_list;

typedef struct s_integers
{
	int	p_x;
	int	p_y;
	int	collectibles;
	int	mooves;
	int	player_last_moove;
	int	status;
}	t_integers;

typedef struct s_vars
{
	char				**map;
	void				*mlx;
	void				*win;
	struct s_img_list	img;
	struct s_integers	integers;
	struct s_mob		*ptr_mob;
	struct s_mob		*mob;
}	t_vars;

void	moove(int keycode, t_vars *vars);
int		init(t_vars *v, char *map_file);
int		parsing(t_vars *vars, char *map_file);

int		print_error(int i);

t_mob	*free_mob(t_vars *vars);
void	load_asset(t_vars *v, char *asset_file, t_img *img);

void	update_map_window(t_vars *vars, int keycode);
void	put_map_window(t_vars *vars);
int		size_map(char **map, char width_or_height);
int		locate_char(char **map, char c, char x_or_y, int occur);

char	**get_map(const char *map_file);
char	*get_next_line(int fd);

#endif
