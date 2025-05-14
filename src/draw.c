/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:16:34 by nbenhami          #+#    #+#             */
/*   Updated: 2025/05/14 12:23:01 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_pixel(t_texture *t, int x, int y, int color)
{
	if (x < 0 || y < 0 || x >= t->width || y >= t->height)
		return;
	int i = y * t->line_len + x * (t->bpp / 8);
	t->buffer[i + 0] = (color & 0x0000FF);
	t->buffer[i + 1] = (color & 0x00FF00) >> 8;
	t->buffer[i + 2] = (color & 0xFF0000) >> 16;
}

void	draw_thick_pixel(t_texture *t, int x, int y, int size, int color)
{
	int dx = -(size / 2);
	int dy = -(size / 2);
	while (dy <= size / 2)
	{
		dx = -(size / 2);
		while (dx <= size / 2)
		{
			draw_pixel(t, x + dx, y + dy, color);
			dx++;
		}
		dy++;
	}
}

void	draw_line(t_texture *t, t_vector2d start, t_vector2d end, int size)
{
	int	dx = fabs(end.x - start.x);
	int	dy = -fabs(end.y - start.y);
	int	sx = (start.x < end.x) ? 1 : -1;
	int	sy = (start.y < end.y) ? 1 : -1;
	int	err = dx + dy;  // erreur = dx + dy (note que dy est négatif)

	int	x = start.x;
	int	y = start.y;
	int	color = 0xFF0000; // couleur blanche, à modifier si tu veux

	while (1)
	{
		draw_thick_pixel(t, x, y, size, color);
		if (x == end.x && y == end.y)
			break;
		int e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y += sy;
		}
	}
}