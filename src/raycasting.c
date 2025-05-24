/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 04:36:28 by nbenhami          #+#    #+#             */
/*   Updated: 2025/05/24 05:13:14 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/raycast.h"

static void	init_wall_rendering(t_game *game, t_render_params *params)
{
	params->fov_rad = (game->player->fov * M_PI) / 180.0;
	params->angle_start = atan2(game->player->dir.y, game->player->dir.x)
		- params->fov_rad / 2;
	params->player_angle = atan2(game->player->dir.y, game->player->dir.x);
	params->player = vector2d_scale(game->player->pos, 32);
}

static t_texture	*get_wall_texture(t_game *game, int side)
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

static int	calculate_wall_height(double hit_x, double hit_y,
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

static void	set_wall_bounds(int wall_height, t_wall_params *wall)
{
	wall->wall_top = (W_HEIGHT / 2) - (wall_height / 2);
	wall->wall_bot = wall->wall_top + wall_height;
	if (wall->wall_bot >= W_HEIGHT)
		wall->wall_bot = W_HEIGHT - 1;
	wall->wall_height = wall_height;
}

static double	calculate_wall_x(t_vector2d hit)
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

static int	get_texture_color(t_texture *tex, int tex_x, int tex_y)
{
	int				tex_i;
	unsigned char	*buf;
	int				color;

	tex_i = tex_y * tex->line_len + tex_x * (tex->bpp / 8);
	buf = (unsigned char *)tex->buffer;
	if (tex_i + 2 >= tex->line_len * tex->height)
		return (0);
	color = (buf[tex_i + 2] << 16) | (buf[tex_i + 1] << 8) | buf[tex_i];
	return (color);
}

static void	draw_wall_pixel(t_game *game, t_texture *tex,
						int col, t_wall_params *wall)
{
	int		tex_x;
	int		y;
	double	tex_pos;
	int		tex_y;
	int		color;

	tex_x = (int)(wall->wall_x * tex->width);
	if (tex_x < 0 || tex_x >= tex->width)
		return ;
	y = wall->wall_top;
	while (y < wall->wall_bot)
	{
		tex_pos = (double)(y - wall->wall_top) / wall->wall_height;
		tex_y = (int)(tex_pos * tex->height);
		if (tex_y >= 0 && tex_y < tex->height)
		{
			color = get_texture_color(tex, tex_x, tex_y);
			if (color != 0)
				draw_pixel(game->render->main_buffer, col, y, color);
		}
		y++;
	}
}

static int	check_textures(t_game *game)
{
	if (!game->tex_man->wall_east || !game->tex_man->wall_south
		|| !game->tex_man->wall_north || !game->tex_man->wall_west)
		return (0);
	return (1);
}

static int	is_hit_valid(t_vector2d hit, t_game *game)
{
	if (hit.x < 0 || hit.y < 0)
		return (0);
	if (hit.x > (game->map->width + 1) * 32)
		return (0);
	if (hit.y > (game->map->height + 1) * 32)
		return (0);
	return (1);
}

static void	cast_ray(t_game *game, t_render_params *params,
					int col, t_ray_data *ray)
{
	t_vector2d	dir;

	ray->ray_angle = params->angle_start + ((double)col / W_WIDTH)
		* (params->fov_rad);
	dir = (t_vector2d){cos(ray->ray_angle), sin(ray->ray_angle)};
	ray->hit = raycast_to_wall(game, params->player, dir, &ray->side);
}

static void	render_wall(t_game *game, t_render_params *params,
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

static void	process_column(t_game *game, t_render_params *params, int col)
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
