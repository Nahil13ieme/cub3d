/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:20:51 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/17 22:01:18 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

t_game	*new_game(void *mlx, void *win, int is_debugging)
{
	t_game	*game;

	if (!mlx || !win)
		return (NULL);
	game = malloc(sizeof(t_game));
	if (!game)
	{
		printf("Malloc error, what did you do ??");
		exit(EXIT_FAILURE);
	}
	game->mlx = mlx;
	game->win = win;
	game->is_debugging = is_debugging;
	game->game_state = RUNNING;
	game->map = NULL;
	game->player = NULL;
	game->render = new_render(game);
	if (is_debugging)
		game->debug = new_debug(game);
	game->destroy = destroy_game;
	return (game);
}

int	game_loop(t_game *game)
{
	(void)game;
	cap_fps();
	game->render->render_loop(game);
	return (1);
}

void	cap_fps(void)
{
	static clock_t	g_last_frame_time = 0;
	clock_t			current;
	clock_t			frame;

	current = clock();
	frame = (current - g_last_frame_time) * 1000 / CLOCKS_PER_SEC;
	if (frame < FRAME_TIME_MS)
		usleep((FRAME_TIME_MS - frame) * 1000);
	g_last_frame_time = clock();
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == 65307)
		game->destroy(game);
	return (0);
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
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
	exit(EXIT_SUCCESS);
}
