/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:40:40 by tle-saut          #+#    #+#             */
/*   Updated: 2025/06/05 13:49:15 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_side_for_y_bounds(t_raycast *ray)
{
	if (ray->step.y > 0)
		ray->side_hit = 1;
	else
		ray->side_hit = 0;
}

void	set_side_for_wall(t_raycast *ray, int side)
{
	if (side == 0)
		set_side_for_x_bounds(ray);
	else
		set_side_for_y_bounds(ray);
}

void	set_side_hit(t_raycast *ray, t_game *game, int side)
{
	if (ray->map_x < 0 || ray->map_x >= game->map->width)
		set_side_for_x_bounds(ray);
	else if (ray->map_y < 0 || ray->map_y >= game->map->height)
		set_side_for_y_bounds(ray);
	else if (game->map->tiles[ray->map_y][ray->map_x] == '1')
		set_side_for_wall(ray, side);
}

int	perform_dda(t_game *game, t_raycast *ray)
{
	int	side;

	side = 0;
	while (1)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_x += ray->step.x;
			side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_y += ray->step.y;
			side = 1;
		}
		if (is_collision(ray, game))
		{
			set_side_hit(ray, game, side);
			break ;
		}
	}
	return (side);
}

t_vector2d	raycast_to_wall(t_game *game, t_vector2d origin, t_vector2d dir,
	int *side_hit)
{
	t_raycast	ray;
	int			side;
	double		distance;

	if (dir.x == 0)
		ray.delta_dist.x = 1e30;
	else
		ray.delta_dist.x = fabs(1.0 / dir.x);
	if (dir.y == 0)
		ray.delta_dist.y = 1e30;
	else
		ray.delta_dist.y = fabs(1.0 / dir.y);
	init_raycast_vars(&ray, origin, dir);
	side = perform_dda(game, &ray);
	*side_hit = ray.side_hit;
	if (side == 0)
		distance = (ray.side_dist.x - ray.delta_dist.x);
	else
		distance = (ray.side_dist.y - ray.delta_dist.y);
	return (vector2d_add(origin, vector2d_scale(dir, distance * 32.0f)));
}
