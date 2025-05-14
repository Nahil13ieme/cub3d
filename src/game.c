/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:20:51 by nbenhami          #+#    #+#             */
/*   Updated: 2025/05/14 16:50:19 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

t_game	*new_game(void *mlx, void *win, int is_debugging, char **av)
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
	game->map = ft_init_map(av[1]);
	if (game->map == NULL)
		return (NULL);
	game->player = ft_init_player(game);
	if (game->player == NULL)
		return (destroy_map(game->map), NULL);
	game->render = new_render(game);
	if (is_debugging)
		game->debug = new_debug(game);
	game->destroy = destroy_game;
	return (game);
}

int	game_loop(t_game *game)
{
	(void)game;
	move_player(game);
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
int	handle_key_release(int keycode, t_game *game)
{
	if (keycode == 'w' || keycode == 's')
		game->player->velocity.y = 0;
	if (keycode == 'a' || keycode == 'd')
		game->player->velocity.x = 0;
	return (0);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == 65307)
		game->destroy(game);
	if (keycode == KEY_W)
		game->player->velocity.y = -0.05f;
	if (keycode == KEY_S)
		game->player->velocity.y = 0.05f;
	if (keycode == KEY_D)
		game->player->velocity.x = 0.05f;
	if (keycode == KEY_A)
		game->player->velocity.x -= 0.05f;
	if (keycode == KEY_LEFT)
		game->player->dir = vector2d_scale(game->player->dir, -.8f);
	if (keycode == KEY_LEFT)
		game->player->dir = vector2d_scale(game->player->dir, -.8f);
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
