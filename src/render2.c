/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:45:09 by tle-saut          #+#    #+#             */
/*   Updated: 2025/06/05 13:46:46 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_circle(t_texture *t, t_vector2d start, int size, int color)
{
	t_vector2d	c;
	t_vector2d	loop;
	t_vector2d	p;
	int			radius;

	radius = size / 2;
	c.x = start.x;
	c.y = start.y;
	loop.y = -radius;
	while (loop.y <= radius)
	{
		loop.x = -radius;
		while (loop.x <= radius)
		{
			if (loop.x * loop.x + loop.y * loop.y <= radius * radius)
			{
				p.x = c.x + loop.x;
				p.y = c.y + loop.y;
				if (p.x >= 0 && p.y >= 0 && p.x < t->width && p.y < t->height)
					draw_pixel(t, p.x, p.y, color);
			}
			loop.x++;
		}
		loop.y++;
	}
}

void	draw_rect(t_texture *t, t_vector2d start, int size, int color)
{
	int			x;
	int			y;
	t_vector2d	p;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			p.x = start.x + x;
			p.y = start.y + y;
			if (p.x < 0 || p.y < 0 || p.x >= t->width || p.y >= t->height)
			{
				x++;
				continue ;
			}
			draw_pixel(t, p.x, p.y, color);
			x++;
		}
		y++;
	}
}

void	clear_buffer(t_texture *t)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	while (y < t->height)
	{
		x = 0;
		while (x < t->width)
		{
			i = y * t->line_len + x * (t->bpp / 8);
			t->buffer[i + 0] = 0;
			t->buffer[i + 1] = 0;
			t->buffer[i + 2] = 0;
			x++;
		}
		y++;
	}
}

void	draw_debug_buffer(t_game *game)
{
	int			x;
	int			y;
	t_texture	*t;
	t_vector2d	player;

	t = game->render->debug_buffer;
	y = 0;
	player = vector2d_scale(game->player->pos, 32);
	raycast_cone(game, t);
	while (y <= game->map->height)
	{
		x = 0;
		while (x <= game->map->width)
		{
			draw_circle(t, player, 8, 0x10DD00);
			if (game->map->tiles[y][x] == '1')
				draw_rect(t, (t_vector2d){32 * x, 32 * y}, 32, 0x0000FF);
			else if (game->map->tiles[y][x] == ' ')
				draw_rect(t, (t_vector2d){32 * x, 32 * y}, 32, 0x800880);
			else if (game->map->tiles[y][x] == 0)
				break ;
			x++;
		}
		y++;
	}
}

int	render_loop(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	clear_buffer(game->render->main_buffer);
	draw_buffer(game);
	mlx_put_image_to_window(game->mlx, game->win,
		game->render->main_buffer->img_ptr, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win,
		game->render->main_buffer->img_ptr, 0, 0);
	if (game->is_debugging)
	{
		mlx_clear_window(game->mlx, game->debug->win);
		clear_buffer(game->render->debug_buffer);
		draw_debug_buffer(game);
		mlx_put_image_to_window(game->mlx, game->debug->win,
			game->render->debug_buffer->img_ptr, 0, 0);
		mlx_put_image_to_window(game->mlx, game->debug->win,
			game->render->debug_buffer->img_ptr, 0, 0);
	}
	return (1);
}
