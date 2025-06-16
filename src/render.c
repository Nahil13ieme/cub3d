/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:16:01 by nbenhami          #+#    #+#             */
/*   Updated: 2025/06/16 13:28:57 by tle-saut         ###   ########.fr       */
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

static int	get_color_from_string(char *str)
{
	char	**parts;
	int		r;
	int		g;
	int		b;
	int		color;

	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2])
		return (0x000000);
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	free(parts[0]);
	free(parts[1]);
	free(parts[2]);
	free(parts);
	color = (r << 16) | (g << 8) | b;
	return (color);
}

void	draw_floor(t_game *game)
{
	int			x;
	int			y;
	int			color;
	t_texture	*t;
	int			i;

	color = get_color_from_string(game->tex_man->floor);
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
			color = get_color_from_string(game->tex_man->cell);
		y++;
	}
}
