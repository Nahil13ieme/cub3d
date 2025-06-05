/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:42:27 by tle-saut          #+#    #+#             */
/*   Updated: 2025/06/05 13:44:02 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
