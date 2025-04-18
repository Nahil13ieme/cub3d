/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:16:01 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/17 22:00:29 by nbenhami         ###   ########.fr       */
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
	r->mlx = game->mlx;
	r->destroy = destroy_render;
	r->render_loop = render_loop;
	return (r);
}

void	draw_buffer(t_game *game)
{
	(void)game;
}

int		render_loop(t_game *game)
{
	draw_buffer(game);
	mlx_put_image_to_window(game->mlx, game->win, game->render->main_buffer->img_ptr, 0, 0);
	return (1);
}

void	destroy_render(t_render *render)
{
	mlx_destroy_image(render->mlx, render->main_buffer->img_ptr);
	free(render->main_buffer);
	free(render);
}