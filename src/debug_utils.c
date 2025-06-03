/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:59:32 by nbenhami          #+#    #+#             */
/*   Updated: 2025/06/03 06:42:23 by nbenhami         ###   ########.fr       */
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

static void	cast_single_ray(t_game *g, t_texture *t,
		t_vector2d player, double ray_angle)
{
	t_vector2d	dir;
	t_vector2d	target;
	int			side;

	dir.x = cos(ray_angle);
	dir.y = sin(ray_angle);
	side = 0;
	target = raycast_to_wall(g, player, dir, &side);
	draw_line(t, player, target, 0xFF0000);
}

void	raycast_cone(t_game *game, t_texture *t)
{
	int			i;
	int			num_rays;
	double		fov_rad;
	double		start_angle;
	t_vector2d	player;

	num_rays = 60;
	i = 0;
	fov_rad = (game->player->fov * M_PI) / 180.0;
	player = vector2d_scale(game->player->pos, 32);
	start_angle = atan2(game->player->dir.y, game->player->dir.x)
		- fov_rad / 2;
	while (i < num_rays)
	{
		cast_single_ray(game, t, player,
			start_angle + (fov_rad / num_rays) * i);
		i++;
	}
}
