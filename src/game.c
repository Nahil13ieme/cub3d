/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:20:51 by nbenhami          #+#    #+#             */
/*   Updated: 2025/05/21 14:05:07 by nbenhami         ###   ########.fr       */
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
	game->tex_man = load_textures(game);
	game->player = ft_init_player(game);
	game->render = new_render(game);
	init_input(game);
	if (is_debugging)
		game->debug = new_debug(game);
	game->destroy = destroy_game;
	return (game);
}

void	input(t_game *game)
{
	t_vector2d	*v;

	v = &game->player->velocity;
	if (game->input.right)
		game->player->dir = vector2d_rotate(game->player->dir, -0.1f);
	if (game->input.left)
		game->player->dir = vector2d_rotate(game->player->dir, 0.1f);
	*v = vector2d(0, 0);
	if (game->input.w)
		*v = vector2d_add(*v, vector2d_scale(game->player->dir, 0.05f));
	if (game->input.s)
		*v = vector2d_substract(*v, vector2d_scale(game->player->dir, 0.05f));
	if (game->input.a)
	{
		v->x += game->player->dir.y * 0.05f;
		v->y -= game->player->dir.x * 0.05f;
	}
	if (game->input.d)
	{
		v->x -= game->player->dir.y * 0.05f;
		v->y += game->player->dir.x * 0.05f;
	}
    if (vector2d_length(*v) > 0.05f)
        *v = vector2d_scale(vector2d_normalize(*v), 0.05f);
}

int	game_loop(t_game *game)
{
	(void)game;
	input(game);
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
	if (keycode == KEY_W)
		game->input.w = false;
	if (keycode == KEY_S)
		game->input.s = false;
	if (keycode == KEY_A)
		game->input.a = false;
	if (keycode == KEY_D)
		game->input.d = false;
	if (keycode == KEY_LEFT)
		game->input.left = false;
	if (keycode == KEY_RIGHT)
		game->input.right = false;
	return (0);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == 65307)
		game->destroy(game);
	if (keycode == KEY_W)
		game->input.w = true;
	if (keycode == KEY_S)
		game->input.s = true;
	if (keycode == KEY_A)
		game->input.a = true;
	if (keycode == KEY_D)
		game->input.d = true;
	if (keycode == KEY_LEFT)
		game->input.left = true;
	if (keycode == KEY_RIGHT)
		game->input.right = true;
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
