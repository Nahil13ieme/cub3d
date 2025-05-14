/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:16:34 by nbenhami          #+#    #+#             */
/*   Updated: 2025/05/14 13:38:52 by nbenhami         ###   ########.fr       */
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

void	draw_line(t_texture *t, t_vector2d start, t_vector2d end, int color)
{
	double dx = end.x - start.x;
	double dy = end.y - start.y;
	double steps = fmax(fabs(dx), fabs(dy));

	if (steps == 0)
		return;

	double x_inc = dx / steps;
	double y_inc = dy / steps;

	double x = start.x;
	double y = start.y;

	for (int i = 0; i <= steps; i++)
	{
		draw_pixel(t, (int)x, (int)y, color);
		x += x_inc;
		y += y_inc;
	}
}
