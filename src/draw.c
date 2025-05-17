/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:16:34 by nbenhami          #+#    #+#             */
/*   Updated: 2025/05/17 15:51:41 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_pixel(t_texture *t, int x, int y, int color)
{
	int	i;

	if (x < 0 || y < 0 || x >= t->width || y >= t->height)
		return ;
	i = y * t->line_len + x * (t->bpp / 8);
	t->buffer[i + 0] = (color & 0x0000FF);
	t->buffer[i + 1] = (color & 0x00FF00) >> 8;
	t->buffer[i + 2] = (color & 0xFF0000) >> 16;
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

t_vector2d	raycast_to_wall(t_game *game, t_vector2d origin, t_vector2d dir)
{
	t_vector2d	step;
	t_vector2d	side_dist;
	t_vector2d	delta_dist;
	t_vector2d	pos;
	int			map_x, map_y;
	int			side = 0;
	pos = vector2d_divide(origin, 32);
	map_x = (int)pos.x;
	map_y = (int)pos.y;
	delta_dist.x = (dir.x == 0) ? 1e30 : fabs(1.0 / dir.x);
	delta_dist.y = (dir.y == 0) ? 1e30 : fabs(1.0 / dir.y);
	if (dir.x < 0)
	{
		step.x = -1;
		side_dist.x = (pos.x - map_x) * delta_dist.x;
	}
	else
	{
		step.x = 1;
		side_dist.x = (map_x + 1.0 - pos.x) * delta_dist.x;
	}
	if (dir.y < 0)
	{
		step.y = -1;
		side_dist.y = (pos.y - map_y) * delta_dist.y;
	}
	else
	{
		step.y = 1;
		side_dist.y = (map_y + 1.0 - pos.y) * delta_dist.y;
	}
	while (1)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			map_x += step.x;
			side = 0;
		}
		else
		{
			side_dist.y += delta_dist.y;
			map_y += step.y;
			side = 1;
		}
		if (map_x < 0 || map_y < 0 || game->map->tiles[map_y][map_x] == '1'
			|| map_y >= game->map->height || map_x >= game->map->width)
			break;
	}
	double distance;
	if (side == 0)
		distance = (side_dist.x - delta_dist.x);
	else
		distance = (side_dist.y - delta_dist.y);
	return (vector2d_add(origin, vector2d_scale(dir, distance * 32.0f)));
}
