/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:16:01 by nbenhami          #+#    #+#             */
/*   Updated: 2025/05/27 14:16:11 by tle-saut         ###   ########.fr       */
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

void	draw_img_to_buffer(t_texture *buffer, t_texture *sprite, int x_offset,
		int y_offset)
{
	int				y;
	int				x;
	char			*src_pixel;
	unsigned int	color;
	char			*dst_pixel;

	if (!buffer->buffer || !sprite->buffer)
		return ;
	y = -1;
	while (++y < sprite->height)
	{
		// Vérifier si le pixel est dans les limites du buffer de destination
		if (y + y_offset < 0 || y + y_offset >= buffer->height)
			continue ;
		x = -1;
		while (++x < sprite->width)
		{
			// Vérifier si le pixel est dans les limites du buffer de destinati
			if (x + x_offset < 0 || x + x_offset >= buffer->width)
				continue ;
			src_pixel = sprite->buffer + (y * sprite->line_len)
				+ (x * (sprite->bpp / 8));
			color = *(unsigned int *)src_pixel;
			if (color && color != 0xFF000000)
			{
				dst_pixel = buffer->buffer + ((y + y_offset) * buffer->line_len)
					+ ((x + x_offset) * (buffer->bpp / 8));
				*(unsigned int *)dst_pixel = color;
			}
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

// void	draw_walls(t_game *game)
// {
// 	double			fov_rad = (game->player->fov * M_PI) / 180.0;
// 	double			angle_start = atan2(game->player->dir.y,
//							game->player->dir.x) - fov_rad / 2;
// 	double			player_angle = atan2(game->player->dir.y, game->player->dir.x);
// 	t_vector2d		player = vector2d_scale(game->player->pos, 32);
// 	t_texture		*tex;
// 	int			side;
// 	if (!game->tex_man->wall_east || !game->tex_man->wall_south
// 		|| !game->tex_man->wall_north || !game->tex_man->wall_west)
// 		return ;
// 	for (int col = 0; col < W_WIDTH; col++)
// 	{
// 		double ray_angle = angle_start + ((double)col / W_WIDTH) * (fov_rad);
// 		t_vector2d dir = { cos(ray_angle), sin(ray_angle) };
// 		t_vector2d hit = raycast_to_wall(game, player, dir, &side);

// 		// Skip if hit is out of map bounds
// 		if (hit.x < 0 || hit.y < 0 || hit.x >= game->map->width * 32 || hit.y >= game->map->height * 32)
// 			continue;

// 		if (side == 0)
// 			tex = game->tex_man->wall_south;
// 		else if (side == 1)
// 			tex = game->tex_man->wall_north;
// 		else if (side == 2)
// 			tex = game->tex_man->wall_west;
// 		else if (side == 3)
// 			tex = game->tex_man->wall_east;
// 		if (!tex)
// 			continue;
// 		double dist = hypot(hit.x - player.x, hit.y - player.y);
// 		if (dist < 0.05f)
// 			continue;
// 		double corrected_dist = dist * cos(ray_angle - player_angle);
// 		double proj_plane_dist = (W_WIDTH / 2.0) / tan(fov_rad / 2.0);
// 		int wall_height = (int)((32.0 / corrected_dist) * proj_plane_dist);
// 		int wall_top = (W_HEIGHT / 2) - (wall_height / 2);
// 		int wall_bot = wall_top + wall_height;
// 		if (wall_bot >= W_HEIGHT) wall_bot = W_HEIGHT - 1;
// 		double wall_x;
// 		double dx = hit.x - floor(hit.x / 32.0) * 32.0;
// 		double dy = hit.y - floor(hit.y / 32.0) * 32.0;
// 		if (fabs(dx - 16) > fabs(dy - 16))
// 			wall_x = hit.y / 32.0;
// 		else
// 			wall_x = hit.x / 32.0;
// 		wall_x -= floor(wall_x);
// 		int tex_x = (int)(wall_x * tex->width);
// 		if (tex_x < 0 || tex_x >= tex->width)
// 			continue;
// 		for (int y = wall_top; y < wall_bot; y++)
// 		{
// 			double tex_pos = (double)(y - wall_top) / wall_height;
// 			int tex_y = (int)(tex_pos * tex->height);
// 			if (tex_y < 0 || tex_y >= tex->height)
// 				continue;
// 			int tex_i = tex_y * tex->line_len + tex_x * (tex->bpp / 8);
// 			unsigned char *buf = (unsigned char *)tex->buffer;
// 			if (tex_i + 2 >= tex->line_len * tex->height)
// 				continue;
// 			int color = (buf[tex_i + 2] << 16) | (buf[tex_i + 1] << 8) | buf[tex_i];
// 			draw_pixel(game->render->main_buffer, col, y, color);
// 		}
// 	}
// }

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
