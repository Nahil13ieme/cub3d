/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:16:34 by nbenhami          #+#    #+#             */
/*   Updated: 2025/06/05 13:48:59 by tle-saut         ###   ########.fr       */
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

void	init_raycast_vars(t_raycast *ray, t_vector2d origin, t_vector2d dir)
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

int	is_collision(t_raycast *ray, t_game *game)
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

void	set_side_for_x_bounds(t_raycast *ray)
{
	if (ray->step.x > 0)
		ray->side_hit = 2;
	else
		ray->side_hit = 3;
}
