/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:44:04 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/17 17:16:49 by nbenhami         ###   ########.fr       */
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

t_texture	*new_texture_from_file(void *mlx, char *file);
t_texture	*new_texture(void *mlx, int width, int height);

#endif /* TEXTURE_H */