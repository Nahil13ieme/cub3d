/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:16:34 by nbenhami          #+#    #+#             */
/*   Updated: 2025/05/24 05:17:04 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/raycast.h"

void	draw_pixel(t_texture *t, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= t->width || y >= t->height)
		return ;
	dst = t->buffer + (y * t->line_len + x * (t->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_line(t_texture *t, t_vector2d start, t_vector2d end, int color)
{
	int			i;
	double		steps;
	t_vector2d	dis;
	t_vector2d	inc;
	t_vector2d	start_inc;

	dis = vector2d(end.x - start.x, end.y - start.y);
	steps = fmax(fabs(dis.x), fabs(dis.y));
	if (steps == 0)
		return ;
	inc = vector2d(dis.x / steps, dis.y / steps);
	start_inc = vector2d(start.x, start.y);
	i = 0;
	while (i <= steps)
	{
		draw_pixel(t, (int)start_inc.x, (int)start_inc.y, color);
		start_inc.x += inc.x;
		start_inc.y += inc.y;
		i++;
	}
}

static void	init_raycast_vars(t_raycast *ray, t_vector2d origin, t_vector2d dir)
{
	ray->pos = vector2d_divide(origin, 32);
	ray->map_x = (int)ray->pos.x;
	ray->map_y = (int)ray->pos.y;
	if (dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (ray->pos.x - ray->map_x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map_x + 1.0 - ray->pos.x) * ray->delta_dist.x;
	}
	if (dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (ray->pos.y - ray->map_y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map_y + 1.0 - ray->pos.y) * ray->delta_dist.y;
	}
}

static int	is_collision(t_raycast *ray, t_game *game)
{
	if (ray->map_x < 0 || ray->map_y < 0)
		return (1);
	if (ray->map_y >= game->map->height)
		return (1);
	if (ray->map_x >= game->map->width)
		return (1);
	if (game->map->tiles[ray->map_y][ray->map_x] == '1')
		return (1);
	return (0);
}

static void	set_side_for_x_bounds(t_raycast *ray)
{
	if (ray->step.x > 0)
		ray->side_hit = 2;
	else
		ray->side_hit = 3;
}

static void	set_side_for_y_bounds(t_raycast *ray)
{
	if (ray->step.y > 0)
		ray->side_hit = 1;
	else
		ray->side_hit = 0;
}

static void	set_side_for_wall(t_raycast *ray, int side)
{
	if (side == 0)
		set_side_for_x_bounds(ray);
	else
		set_side_for_y_bounds(ray);
}

static void	set_side_hit(t_raycast *ray, t_game *game, int side)
{
	if (ray->map_x < 0 || ray->map_x >= game->map->width)
		set_side_for_x_bounds(ray);
	else if (ray->map_y < 0 || ray->map_y >= game->map->height)
		set_side_for_y_bounds(ray);
	else if (game->map->tiles[ray->map_y][ray->map_x] == '1')
		set_side_for_wall(ray, side);
}

static int	perform_dda(t_game *game, t_raycast *ray)
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
