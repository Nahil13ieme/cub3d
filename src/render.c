/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:16:01 by nbenhami          #+#    #+#             */
/*   Updated: 2025/06/03 06:50:03 by nbenhami         ###   ########.fr       */
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
	r->debug_buffer = new_texture(game->mlx,
			(game->map->width + 1) * 32, (game->map->height + 1) * 32);
	if (!r->debug_buffer)
		return (NULL);
	r->mlx = game->mlx;
	r->destroy = destroy_render;
	r->render_loop = render_loop;
	return (r);
}

static void	copy_pixel(t_draw_pixel_info info, int x, int y)
{
	char			*src_pixel;
	char			*dst_pixel;
	unsigned int	color;

	src_pixel = info.s->buffer + (y * info.s->line_len)
		+ (x * (info.s->bpp / 8));
	color = *(unsigned int *)src_pixel;
	if (color && color != 0xFF000000)
	{
		dst_pixel = info.b->buffer + ((y + info.y_offset) * info.b->line_len)
			+ ((x + info.x_offset) * (info.b->bpp / 8));
		*(unsigned int *)dst_pixel = color;
	}
}

void	draw_img_to_buffer(t_texture *b, t_texture *s,
	int x_offset, int y_offset)
{
	int					x;
	int					y;
	t_draw_pixel_info	info;

	if (!b->buffer || !s->buffer)
		return ;
	info.b = b;
	info.s = s;
	info.x_offset = x_offset;
	info.y_offset = y_offset;
	y = -1;
	while (++y < s->height)
	{
		if (y + y_offset < 0 || y + y_offset >= b->height)
			continue ;
		x = -1;
		while (++x < s->width)
		{
			if (x + x_offset < 0 || x + x_offset >= b->width)
				continue ;
			copy_pixel(info, x, y);
		}
	}
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

void	draw_buffer(t_game *game)
{
	draw_floor(game);
	draw_walls(game);
}

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
	if (game->is_debugging)
	{
		mlx_clear_window(game->mlx, game->debug->win);
		clear_buffer(game->render->debug_buffer);
		draw_debug_buffer(game);
		mlx_put_image_to_window(game->mlx, game->debug->win,
			game->render->debug_buffer->img_ptr, 0, 0);
	}
	return (1);
}

void	destroy_render(t_render *render)
{
	mlx_destroy_image(render->mlx, render->main_buffer->img_ptr);
	mlx_destroy_image(render->mlx, render->debug_buffer->img_ptr);
	free(render->debug_buffer);
	free(render->main_buffer);
	free(render);
}
