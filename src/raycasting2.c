/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:35:08 by tle-saut          #+#    #+#             */
/*   Updated: 2025/06/05 13:49:58 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_hit_valid(t_vector2d hit, t_game *game)
{
	if (hit.x < 0 || hit.y < 0)
		return (0);
	if (hit.x > (game->map->width + 1) * 32)
		return (0);
	if (hit.y > (game->map->height + 1) * 32)
		return (0);
	return (1);
}

void	cast_ray(t_game *game, t_render_params *params,
					int col, t_ray_data *ray)
{
	t_vector2d	dir;

	ray->ray_angle = params->angle_start + ((double)col / W_WIDTH)
		* (params->fov_rad);
	dir = (t_vector2d){cos(ray->ray_angle), sin(ray->ray_angle)};
	ray->hit = raycast_to_wall(game, params->player, dir, &ray->side);
}

void	render_wall(t_game *game, t_render_params *params,
					int col, t_ray_data *ray)
{
	t_texture		*tex;
	t_wall_params	wall;
	int				wall_height;

	tex = get_wall_texture(game, ray->side);
	if (!tex)
	{
		printf("Error - Texture not found\n");
		return ;
	}
	wall_height = calculate_wall_height(ray->hit.x, ray->hit.y,
			params, ray->ray_angle);
	if (wall_height <= 0)
	{
		printf("Error - Wall height is zero or negative\n");
		return ;
	}
	set_wall_bounds(wall_height, &wall);
	wall.wall_x = calculate_wall_x(ray->hit);
	draw_wall_pixel(game, tex, col, &wall);
}

void	process_column(t_game *game, t_render_params *params, int col)
{
	t_ray_data	ray;

	cast_ray(game, params, col, &ray);
	if (!is_hit_valid(ray.hit, game))
	{
		printf("Error - Hit out of bounds\n");
	}
	render_wall(game, params, col, &ray);
}

void	draw_walls(t_game *game)
{
	t_render_params	params;
	int				col;

	if (!check_textures(game))
	{
		printf("Error - Textures not loaded\n");
		return ;
	}
	init_wall_rendering(game, &params);
	col = 0;
	while (col < W_WIDTH)
	{
		process_column(game, &params, col);
		col++;
	}
}
