/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:59:32 by nbenhami          #+#    #+#             */
/*   Updated: 2025/05/22 17:18:31 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <sys/time.h>

long	get_time_microseconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000L + tv.tv_usec);
}

void	raycast_cone(t_game *game, t_texture *t)
{
	int			num_rays;
	int			i;
	double		fov_rad;
	t_vector2d	player;
	t_vector2d	target;
	double		start_angle;
	double		ray_angle;
	t_vector2d	dir;
	int			side;

	side = 0;
	num_rays = 60;
	i = 0;
	fov_rad = (game->player->fov * M_PI) / 180.0;
	player = vector2d_scale(game->player->pos, 32);
	start_angle = atan2(game->player->dir.y, game->player->dir.x) - fov_rad / 2;
	while (i < num_rays)
	{
		ray_angle = start_angle + (fov_rad / num_rays) * i;
		dir.x = cos(ray_angle);
		dir.y = sin(ray_angle);
		target = raycast_to_wall(game, player, dir, &side);
		draw_line(t, player, target, 0xFF0000);
		i++;
	}
}
