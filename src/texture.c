/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:01:17 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/17 21:13:29 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/texture.h"

t_texture	*new_texture_from_file(void *mlx, char *file)
{
	t_texture	*t;
	int			height;
	int			width;

	t = malloc(sizeof(t_texture));
	if (!t)
		return (NULL);
	t->img_ptr = mlx_xpm_file_to_image(mlx, file, &height, &width);
	t->height = height;
	t->width = width;
	return (t);
}

t_texture	*new_texture(void *mlx, int width, int height)
{
	t_texture	*t;

	t = malloc(sizeof(t_texture));
	if (!t)
		return (NULL);
	t->img_ptr = mlx_new_image(mlx, width, height);
	t->buffer = mlx_get_data_addr(t->img_ptr, &t->bpp, &t->line_len, &t->endian);
	t->width = width;
	t->height = height;
	return (t);
}
