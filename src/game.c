/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:20:51 by nbenhami          #+#    #+#             */
/*   Updated: 2025/06/03 06:52:32 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

static t_game	*new_game2(t_game *game, int is_debugging)
{
	game->player = ft_init_player(game);
	if (!game->player)
		return (destroy_map(game->map), NULL);
	game->render = new_render(game);
	init_input(game);
	if (is_debugging)
		game->debug = new_debug(game);
	game->destroy = destroy_game;
	return (game);
}

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
	game->files[0] = "asset/wall_north.xpm";
	game->files[1] = "asset/wall_south2.xpm";
	game->files[2] = "asset/wall_north.xpm";
	game->files[3] = "asset/wall_south2.xpm";
	game->mlx = mlx;
	game->win = win;
	game->is_debugging = is_debugging;
	game->game_state = RUNNING;
	game->map = ft_init_map(av[1]);
	game->tex_man = load_textures(game);
	if (game->map == NULL)
		return (NULL);
	return (new_game2(game, is_debugging));
}

static void	input_lateral(t_game *g, t_vector2d *v)
{
	if (g->input.a)
	{
		v->x += g->player->dir.y * g->player->speed;
		v->y -= g->player->dir.x * g->player->speed;
	}
	if (g->input.d)
	{
		v->x -= g->player->dir.y * g->player->speed;
		v->y += g->player->dir.x * g->player->speed;
	}
}

void	input(t_game *game)
{
	t_vector2d	*v;

	v = &game->player->velocity;
	if (game->input.maj)
		game->player->speed = 0.12f;
	else
		game->player->speed = 0.08f;
	if (game->input.left)
		game->player->dir = vector2d_rotate(game->player->dir, -0.1f);
	if (game->input.right)
		game->player->dir = vector2d_rotate(game->player->dir, 0.1f);
	*v = vector2d(0, 0);
	if (game->input.w)
		*v = vector2d_add(*v, vector2d_scale(game->player->dir,
					game->player->speed));
		*v = vector2d_add(*v, vector2d_scale(game->player->dir,
					game->player->speed));
	if (game->input.s)
		*v = vector2d_substract(*v, vector2d_scale(game->player->dir,
					game->player->speed));
	input_lateral(game, v);
	if (vector2d_length(*v) > game->player->speed)
		*v = vector2d_scale(vector2d_normalize(*v), game->player->speed);
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
	if (keycode == KEY_MAJ)
		game->input.maj = false;
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
	if (keycode == KEY_MAJ)
		game->input.maj = true;
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
