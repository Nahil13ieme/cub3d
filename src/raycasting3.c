/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:36:19 by tle-saut          #+#    #+#             */
/*   Updated: 2025/06/05 13:50:15 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_wall_pixel(t_game *game, t_texture *tex,
	int col, t_wall_params *wall)
{
	int		tex_x;
	int		y;
	double	tex_pos;
	int		tex_y;
	int		color;

	tex_x = (int)(wall->wall_x * tex->width);
	if (tex_x < 0 || tex_x >= tex->width)
		return ;
	y = wall->wall_top;
	while (y < wall->wall_bot)
	{
		tex_pos = (double)(y - wall->wall_top) / wall->wall_height;
		tex_y = (int)(tex_pos * tex->height);
		if (tex_y >= 0 && tex_y < tex->height)
		{
			color = get_texture_color(tex, tex_x, tex_y);
			if (color != 0)
				draw_pixel(game->render->main_buffer, col, y, color);
		}
		y++;
	}
}

int	check_textures(t_game *game)
{
	if (!game->tex_man->wall_east || !game->tex_man->wall_south
		|| !game->tex_man->wall_north || !game->tex_man->wall_west)
		return (0);
	return (1);
}

int	get_texture_color(t_texture *tex, int tex_x, int tex_y)
{
	int				tex_i;
	unsigned char	*buf;
	int				color;

	tex_i = tex_y * tex->line_len + tex_x * (tex->bpp / 8);
	buf = (unsigned char *)tex->buffer;
	if (tex_i + 2 >= tex->line_len * tex->height)
		return (0);
	color = (buf[tex_i + 2] << 16) | (buf[tex_i + 1] << 8) | buf[tex_i];
	return (color);
}
