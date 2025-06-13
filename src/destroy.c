/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:30:57 by tle-saut          #+#    #+#             */
/*   Updated: 2025/06/13 13:15:13 by nbenhami         ###   ########.fr       */
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
	free(game->tex_man->wall_east);
	free(game->tex_man->wall_north);
	free(game->tex_man->wall_south);
	free(game->tex_man->wall_west);
	//free(game->tex_man->cell);
	//free(game->tex_man->floor);
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
	mlx_destroy_image(game->mlx, game->tex_man->wall_east->img_ptr);
	mlx_destroy_image(game->mlx, game->tex_man->wall_north->img_ptr);
	mlx_destroy_image(game->mlx, game->tex_man->wall_south->img_ptr);
	mlx_destroy_image(game->mlx, game->tex_man->wall_west->img_ptr);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game->pathe);
	free(game->paths);
	free(game->pathn);
	free(game->pathw);
	free_tex_man(game);
	free(game);
	exit(EXIT_SUCCESS);
}

void	destroy_render(t_render *render)
{
	mlx_destroy_image(render->mlx, render->main_buffer->img_ptr);
	mlx_destroy_image(render->mlx, render->debug_buffer->img_ptr);
	free(render->debug_buffer);
	free(render->main_buffer);
	free(render);
}

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
	mlx_destroy_image(game->mlx, game->tex_man->wall_east->img_ptr);
	mlx_destroy_image(game->mlx, game->tex_man->wall_north->img_ptr);
	mlx_destroy_image(game->mlx, game->tex_man->wall_south->img_ptr);
	mlx_destroy_image(game->mlx, game->tex_man->wall_west->img_ptr);
	free_texture_before(game->tex_man);
}
