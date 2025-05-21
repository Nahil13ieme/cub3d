/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:16:34 by nbenhami          #+#    #+#             */
/*   Updated: 2025/05/18 15:35:58 by nbenhami         ###   ########.fr       */
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
		if (ray->map_x < 0 || ray->map_y < 0
			|| game->map->tiles[ray->map_y][ray->map_x] == '1'
			|| ray->map_y >= game->map->height
			|| ray->map_x >= game->map->width)
			break ;
	}
	return (side);
}

t_vector2d	raycast_to_wall(t_game *game, t_vector2d origin, t_vector2d dir)
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
	if (side == 0)
		distance = (ray.side_dist.x - ray.delta_dist.x);
	else
		distance = (ray.side_dist.y - ray.delta_dist.y);
	return (vector2d_add(origin, vector2d_scale(dir, distance * 32.0f)));
}
