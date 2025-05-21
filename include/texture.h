/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:44:04 by nbenhami          #+#    #+#             */
/*   Updated: 2025/05/21 14:03:44 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "cub3d.h"

typedef struct s_texture
{
	void	*img_ptr;
	char	*buffer;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_texture;

typedef struct s_texture_manager
{
	t_texture	*wall_north;
	t_texture	*wall_south;
	t_texture	*wall_east;
	t_texture	*wall_west;
}	t_texture_manager;

t_texture			*new_texture_from_file(void *mlx, char *file);
t_texture			*new_texture(void *mlx, int width, int height);
t_texture_manager	*load_textures(t_game *game);

#endif /* TEXTURE_H */