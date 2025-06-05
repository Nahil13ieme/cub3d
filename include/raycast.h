/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:24:55 by nbenhami          #+#    #+#             */
/*   Updated: 2025/06/05 14:33:33 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "cub3d.h"

typedef struct s_texture	t_texture;

typedef struct s_raycast
{
	t_vector2d	step;
	t_vector2d	side_dist;
	t_vector2d	delta_dist;
	t_vector2d	pos;
	int			map_x;
	int			map_y;
	int			side_hit;
}	t_raycast;

typedef struct s_render_params
{
	double		fov_rad;
	double		angle_start;
	double		player_angle;
	t_vector2d	player;
}	t_render_params;

typedef struct s_wall_params
{
	int			wall_top;
	int			wall_bot;
	int			wall_height;
	double		wall_x;
}	t_wall_params;

typedef struct s_ray_data
{
	t_vector2d	hit;
	int			side;
	double		ray_angle;
}	t_ray_data;

void		draw_pixel(t_texture *t, int x, int y, int color);
void		draw_line(t_texture *t, t_vector2d start, t_vector2d end,
				int color);
t_vector2d	raycast_to_wall(t_game *game, t_vector2d origin,
				t_vector2d dir, int *side_hit);

#endif // RAYCAST_H
