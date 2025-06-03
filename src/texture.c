/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:01:17 by nbenhami          #+#    #+#             */
/*   Updated: 2025/06/03 06:52:49 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/texture.h"
#include "texture.h"

t_texture	*new_texture_from_file(void *mlx, char *file)
{
	t_texture	*t;
	int			width;
	int			height;

	t = malloc(sizeof(t_texture));
	if (!t)
		return (NULL);
	t->img_ptr = mlx_xpm_file_to_image(mlx, file, &width, &height);
	if (!t->img_ptr)
	{
		free(t);
		return (NULL);
	}
	t->buffer = mlx_get_data_addr(t->img_ptr, &t->bpp,
			&t->line_len, &t->endian);
	t->width = width;
	t->height = height;
	return (t);
}

t_texture	*new_texture(void *mlx, int width, int height)
{
	t_texture	*t;

	t = malloc(sizeof(t_texture));
	if (!t)
		return (NULL);
	t->img_ptr = mlx_new_image(mlx, width, height);
	t->buffer = mlx_get_data_addr(t->img_ptr, &t->bpp,
			&t->line_len, &t->endian);
	t->width = width;
	t->height = height;
	return (t);
}

t_texture_manager	*load_textures(t_game *game)
{
	t_texture_manager	*tex_man;

	tex_man = malloc(sizeof(t_texture_manager));
	if (!tex_man)
		return (NULL);
	tex_man->wall_north = new_texture_from_file(game->mlx, game->files[0]);
	tex_man->wall_south = new_texture_from_file(game->mlx, game->files[1]);
	tex_man->wall_east = new_texture_from_file(game->mlx, game->files[2]);
	tex_man->wall_west = new_texture_from_file(game->mlx, game->files[3]);
	return (tex_man);
}
