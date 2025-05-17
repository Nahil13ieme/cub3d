/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:16:34 by nbenhami          #+#    #+#             */
/*   Updated: 2025/05/17 19:44:36 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

typedef struct s_raycast
{
	t_vector2d	step;
	t_vector2d	side_dist;
	t_vector2d	delta_dist;
	t_vector2d	pos;
	int			map_x;
	int			map_y;
}	t_raycast;

void	draw_pixel(t_texture *t, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= t->width || y >= t->height)
		return ;
	dst = t->buffer + (y * t->line_len + x * (t->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_line_low(t_texture *t, int x0, int y0, int x1, int y1, int color)
{
	int	dx;
	int	dy;
	int	yi;
	int	d;
	int	y;
	int	x;

	dx = x1 - x0;
	dy = y1 - y0;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	d = (2 * dy) - dx;
	y = y0;
	x = x0;
	while (x <= x1)
	{
		draw_pixel(t, x, y, color);
		if (d > 0)
		{
			y += yi;
			d += 2 * (dy - dx);
		}
		else
			d += 2 * dy;
		x++;
	}
}

void	draw_line_high(t_texture *t, int x0, int y0, int x1, int y1, int color)
{
	int	dx;
	int	dy;
	int	xi;
	int	d;
	int	y;
	int	x;

	dx = x1 - x0;
	dy = y1 - y0;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	d = (2 * dx) - dy;
	y = y0;
	x = x0;
	while (y <= y1)
	{
		draw_pixel(t, x, y, color);
		if (d > 0)
		{
			x += xi;
			d += 2 * (dx - dy);
		}
		else
			d += 2 * dx;
		y++;
	}
}

void	draw_line(t_texture *t, t_vector2d start, t_vector2d end, int color)
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;

	x0 = (int)start.x;
	y0 = (int)start.y;
	x1 = (int)end.x;
	y1 = (int)end.y;
	if (abs(y1 - y0) < abs(x1 - x0))
	{
		if (x0 > x1)
			draw_line_low(t, x1, y1, x0, y0, color);
		else
			draw_line_low(t, x0, y0, x1, y1, color);
	}
	else
	{
		if (y0 > y1)
			draw_line_high(t, x1, y1, x0, y0, color);
		else
			draw_line_high(t, x0, y0, x1, y1, color);
	}
}

void	init_raycast_vars(t_raycast *ray, t_vector2d origin, t_vector2d dir)
{
	ray->pos = vector2d_divide(origin, 32);
	ray->map_x = (int)ray->pos.x;
	ray->map_y = (int)ray->pos.y;
	ray->delta_dist.x = (dir.x == 0) ? 1e30 : fabs(1.0 / dir.x);
	ray->delta_dist.y = (dir.y == 0) ? 1e30 : fabs(1.0 / dir.y);
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
		if (ray->map_x < 0 || ray->map_y < 0 || 
			game->map->tiles[ray->map_y][ray->map_x] == '1' ||
			ray->map_y >= game->map->height || 
			ray->map_x >= game->map->width)
			break ;
	}
	return (side);
}

t_vector2d	raycast_to_wall(t_game *game, t_vector2d origin, t_vector2d dir)
{
	t_raycast	ray;
	int			side;
	double		distance;

	init_raycast_vars(&ray, origin, dir);
	side = perform_dda(game, &ray);
	if (side == 0)
		distance = (ray.side_dist.x - ray.delta_dist.x);
	else
		distance = (ray.side_dist.y - ray.delta_dist.y);
	return (vector2d_add(origin, vector2d_scale(dir, distance * 32.0f)));
}
