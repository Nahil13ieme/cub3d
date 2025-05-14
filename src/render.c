/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:16:01 by nbenhami          #+#    #+#             */
/*   Updated: 2025/05/14 12:23:55 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/render.h"

t_render	*new_render(t_game *game)
{
	t_render	*r;

	r = malloc(sizeof(t_render));
	if (!r)
		return (NULL);
	r->main_buffer = new_texture(game->mlx, W_WIDTH, W_HEIGHT);
	if (!r->main_buffer)
		return (NULL);
	r->debug_buffer = new_texture(game->mlx, (game->map->width + 1) * 32, (game->map->height + 1) * 32);
		if (!r->debug_buffer)
			return (NULL);
	r->mlx = game->mlx;
	r->destroy = destroy_render;
	r->render_loop = render_loop;
	return (r);
}

void	draw_floor(t_game *game)
{
	int			x;
	int			y;
	int			color;
	t_texture	*t;
	int			i;

	color = 0x0000FF;
	t = game->render->main_buffer;
	y = 0;
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			i = y * t->line_len + x * (t->bpp / 8);
			t->buffer[i + 0] = (color & 0x0000FF);
			t->buffer[i + 1] = (color & 0x00FF00) >> 8;
			t->buffer[i + 2] = (color & 0xFF0000) >> 16;
			x++;
		}
		if (y > W_HEIGHT / 2)
			color = 0x00FF00;
		y++;
	}
}

void	draw_walls(t_game *game)
{
	(void)game;
}

void	draw_buffer(t_game *game)
{
	draw_floor(game);
}

void	draw_circle(t_texture *t, int start_x, int start_y, int size, int color)
{
	int	radius = size / 2;
	int	cx = start_x + radius;
	int	cy = start_y + radius;
	int	x = -radius;
	int	y = -radius;

	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
			{
				int px = cx + x;
				int py = cy + y;
				if (px >= 0 && py >= 0 && px < t->width && py < t->height)
				{
					int i = py * t->line_len + px * (t->bpp / 8);
					t->buffer[i + 0] = (color & 0x0000FF);
					t->buffer[i + 1] = (color & 0x00FF00) >> 8;
					t->buffer[i + 2] = (color & 0xFF0000) >> 16;
				}
			}
			x++;
		}
		y++;
	}
}


void	draw_rect(t_texture *t, int start_x, int start_y, int size, int color)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			int px = start_x + x;
			int py = start_y + y;
			if (px < 0 || py < 0 || px >= t->width || py >= t->height)
			{
				x++;
				continue;
			}
			i = py * t->line_len + px * (t->bpp / 8);
			t->buffer[i + 0] = (color & 0x0000FF);
			t->buffer[i + 1] = (color & 0x00FF00) >> 8;
			t->buffer[i + 2] = (color & 0xFF0000) >> 16;
			x++;
		}
		y++;
	}
}

void	clear_buffer(t_texture *t)
{
	int	x;
	int	y;

	y = 0;
	while (y < t->height)
	{
		x = 0;
		while (x < t->width)
		{
			int i = y * t->line_len + x * (t->bpp / 8);
			t->buffer[i + 0] = 0; // Bleu
			t->buffer[i + 1] = 0; // Vert
			t->buffer[i + 2] = 0; // Rouge
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
	int			color;

	t = game->render->debug_buffer;
	color = 0x0000FF;
	y = 0;
	while (y <= game->map->height)
	{
		x = 0;
		while (x <= game->map->width)
		{
			draw_circle(t, game->player->pos.x * 32, game->player->pos.y * 32, 8, 0x00DD00);
			if (game->map->tiles[y][x] == '1')
				draw_rect(t, x * 32, y * 32, 32, color);
			else if (game->map->tiles[y][x] == ' ')
				draw_rect(t, x * 32, y * 32, 32, 0x909090);
			else if (game->map->tiles[y][x] == 0)
				break ;
			x++;
		}
		y++;
	}
}


int		render_loop(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	draw_buffer(game);
	mlx_put_image_to_window(game->mlx, game->win, game->render->main_buffer->img_ptr, 0, 0);
	if (game->is_debugging)
	{
		mlx_clear_window(game->mlx, game->debug->win);
		clear_buffer(game->render->debug_buffer);
		draw_debug_buffer(game);
		mlx_put_image_to_window(game->mlx, game->debug->win, game->render->debug_buffer->img_ptr, 0, 0);
	}
	return (1);
}

void	destroy_render(t_render *render)
{
	mlx_destroy_image(render->mlx, render->main_buffer->img_ptr);
	free(render->main_buffer);
	free(render);
}