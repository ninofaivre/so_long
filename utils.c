/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nino <nino@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:39:04 by nino              #+#    #+#             */
/*   Updated: 2021/11/09 18:00:58 by nino             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_mob	*free_mob(t_vars *vars)
{
	while (vars->ptr_mob)
	{
		vars->mob = vars->ptr_mob;
		vars->ptr_mob = vars->ptr_mob->next;
		free(vars->mob);
	}
	return ((t_mob *) -1);
}

void	load_asset(t_vars *v, char *asset_file, t_img *img)
{
	img->img = mlx_xpm_file_to_image(v->mlx, asset_file,
			&img->width, &img->height);
}
