/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:52:35 by tle-saut          #+#    #+#             */
/*   Updated: 2025/06/16 13:46:06 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	destroy_game_before(t_game *game, int sel)
{
	if (game->is_debugging && game->debug)
		game->debug->destroy(&game->debug);
	if (game->map)
		game->map->destroy(game->map);
	if (sel == 1)
	{
		free(game->pathe);
		free(game->paths);
		free(game->pathn);
		free(game->pathw);
		free_tex_man(game);
	}
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
	exit(EXIT_SUCCESS);
}

void	free_texture_before(t_texture_manager *text)
{
	free(text->wall_east);
	free(text->wall_west);
	free(text->wall_south);
	free(text->wall_north);
	free(text);
}

void	destroy_img(t_game *game, int sel)
{
	if (sel == 1)
	{
		free(game->pathe);
		free(game->paths);
		free(game->pathn);
		free(game->pathw);
	}
	if (game->tex_man->wall_east)
		mlx_destroy_image(game->mlx, game->tex_man->wall_east->img_ptr);
	if (game->tex_man->wall_north)
		mlx_destroy_image(game->mlx, game->tex_man->wall_north->img_ptr);
	if (game->tex_man->wall_south)
		mlx_destroy_image(game->mlx, game->tex_man->wall_south->img_ptr);
	if (game->tex_man->wall_west)
		mlx_destroy_image(game->mlx, game->tex_man->wall_west->img_ptr);
	free(game->tex_man->floor);
	free(game->tex_man->cell);
	free_texture_before(game->tex_man);
	printf("Error\nfrom texture\n");
}
