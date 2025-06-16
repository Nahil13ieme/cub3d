/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:30:57 by tle-saut          #+#    #+#             */
/*   Updated: 2025/06/16 13:16:03 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	destroy_player(t_player *player)
{
	t_player	*fplayer;

	fplayer = (t_player *)player;
	free(fplayer);
}

void	free_tex_man(t_game *game)
{
	if (!game->tex_man)
		return ;
	free(game->tex_man->wall_east);
	free(game->tex_man->wall_north);
	free(game->tex_man->wall_south);
	free(game->tex_man->wall_west);
	free(game->tex_man->cell);
	free(game->tex_man->floor);
	free(game->tex_man);
}

void	destroy_game(t_game *game)
{
	if (game->is_debugging && game->debug)
		game->debug->destroy(&game->debug);
	if (game->player)
		game->player->destroy(game->player);
	if (game->map)
		game->map->destroy(game->map);
	if (game->render)
		game->render->destroy(game->render);
	if (game->tex_man->wall_east->img_ptr)
		mlx_destroy_image(game->mlx, game->tex_man->wall_east->img_ptr);
	if (game->tex_man->wall_north->img_ptr)
		mlx_destroy_image(game->mlx, game->tex_man->wall_north->img_ptr);
	if (game->tex_man->wall_south->img_ptr)
		mlx_destroy_image(game->mlx, game->tex_man->wall_south->img_ptr);
	if (game->tex_man->wall_west->img_ptr)
		mlx_destroy_image(game->mlx, game->tex_man->wall_west->img_ptr);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_path(game);
	free_tex_man(game);
	free(game);
	exit(EXIT_SUCCESS);
}

void	free_path(t_game *game)
{
	free(game->pathe);
	free(game->paths);
	free(game->pathn);
	free(game->pathw);
}

void	destroy_render(t_render *render)
{
	mlx_destroy_image(render->mlx, render->main_buffer->img_ptr);
	mlx_destroy_image(render->mlx, render->debug_buffer->img_ptr);
	free(render->debug_buffer);
	free(render->main_buffer);
	free(render);
}
