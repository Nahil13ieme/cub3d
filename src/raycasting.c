/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 04:36:28 by nbenhami          #+#    #+#             */
/*   Updated: 2025/06/05 13:49:43 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/raycast.h"

void	init_wall_rendering(t_game *game, t_render_params *params)
{
	params->fov_rad = (game->player->fov * M_PI) / 180.0;
	params->angle_start = atan2(game->player->dir.y, game->player->dir.x)
		- params->fov_rad / 2;
	params->player_angle = atan2(game->player->dir.y, game->player->dir.x);
	params->player = vector2d_scale(game->player->pos, 32);
}

t_texture	*get_wall_texture(t_game *game, int side)
{
	if (side == 0)
		return (game->tex_man->wall_south);
	else if (side == 1)
		return (game->tex_man->wall_north);
	else if (side == 2)
		return (game->tex_man->wall_west);
	else if (side == 3)
		return (game->tex_man->wall_east);
	printf("Error - Invalid side hit = %d\n", side);
	return (NULL);
}

int	calculate_wall_height(double hit_x, double hit_y,
							t_render_params *params, double ray_angle)
{
	double	dist;
	double	corrected_dist;
	double	proj_plane_dist;
	int		wall_height;

	dist = hypot(hit_x - params->player.x, hit_y - params->player.y);
	if (dist < 1.f)
		return (0);
	corrected_dist = dist * cos(ray_angle - params->player_angle);
	proj_plane_dist = (W_WIDTH / 2.0) / tan(params->fov_rad / 2.0);
	wall_height = (int)((32.0 / corrected_dist) * proj_plane_dist);
	return (wall_height);
}

void	set_wall_bounds(int wall_height, t_wall_params *wall)
{
	wall->wall_top = (W_HEIGHT / 2) - (wall_height / 2);
	wall->wall_bot = wall->wall_top + wall_height;
	if (wall->wall_bot >= W_HEIGHT)
		wall->wall_bot = W_HEIGHT - 1;
	wall->wall_height = wall_height;
}

double	calculate_wall_x(t_vector2d hit)
{
	double	wall_x;
	double	dx;
	double	dy;

	dx = hit.x - floor(hit.x / 32.0) * 32.0;
	dy = hit.y - floor(hit.y / 32.0) * 32.0;
	if (fabs(dx - 16) > fabs(dy - 16))
		wall_x = hit.y / 32.0;
	else
		wall_x = hit.x / 32.0;
	wall_x -= floor(wall_x);
	return (wall_x);
}
