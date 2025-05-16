/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:16:01 by nbenhami          #+#    #+#             */
/*   Updated: 2025/05/16 19:40:31 by nbenhami         ###   ########.fr       */
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
	double			fov_rad = (game->player->fov * M_PI) / 180.0;
	double			angle_start = atan2(game->player->dir.y, game->player->dir.x) - fov_rad / 2;
	t_vector2d		player = vector2d_scale(game->player->pos, 32); // en pixels

	for (int col = 0; col < W_WIDTH; col++)
	{
		// Angle du rayon pour cette colonne
		double ray_angle = angle_start + ((double)col / W_WIDTH) * fov_rad;
		t_vector2d dir = { cos(ray_angle), sin(ray_angle) };

		// Point d'impact du rayon
		t_vector2d hit = raycast_to_wall(game, player, dir);

		// Distance (avec correction fish-eye)
		double dist = hypot(hit.x - player.x, hit.y - player.y);
		double corrected_dist = dist * cos(ray_angle - atan2(game->player->dir.y, game->player->dir.x));

		// Calcul de la hauteur du mur
		double proj_plane_dist = (W_WIDTH / 2.0) / tan(fov_rad / 2.0);
		int wall_height = (int)((32.0 / corrected_dist) * proj_plane_dist);

		// Déterminer les bornes de dessin
		int wall_top = (W_HEIGHT / 2) - (wall_height / 2);
		int wall_bot = wall_top + wall_height;
		if (wall_top < 0) wall_top = 0;
		if (wall_bot >= W_HEIGHT) wall_bot = W_HEIGHT - 1;

		// Dessiner le mur (ligne verticale)
		for (int y = wall_top; y < wall_bot; y++)
		{
			draw_pixel(game->render->main_buffer, col, y, 0xFF0000); // couleur rouge
		}
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
				continue;
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

void	raycast_cone(t_game *game, t_texture *t)
{
	int			num_rays = 60;
	int			i;
	double		fov_rad = (game->player->fov * M_PI) / 180.0;
	t_vector2d	player = vector2d_scale(game->player->pos, 32);
	double		start_angle = atan2(game->player->dir.y, game->player->dir.x) - fov_rad / 2;

	for (i = 0; i < num_rays; i++)
	{
		double ray_angle = start_angle + (fov_rad / num_rays) * i;
		t_vector2d dir = {
			cos(ray_angle),
			sin(ray_angle)
		};
		t_vector2d target = raycast_to_wall(game, player, dir);
		draw_line(t, player, target, 0xFF0000);
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
	while (y <= game->map->height)
	{
		x = 0;
		while (x <= game->map->width)
		{
			raycast_cone(game, t);
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

int		render_loop(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	clear_buffer(game->render->main_buffer);
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
	mlx_destroy_image(render->mlx, render->debug_buffer->img_ptr);
	free(render->debug_buffer);
	free(render->main_buffer);
	free(render);
}