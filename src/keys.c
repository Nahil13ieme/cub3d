/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:22:24 by tle-saut          #+#    #+#             */
/*   Updated: 2025/05/16 15:00:34 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	key_pressed(int keycode, t_game *game)
{
	if (keycode == 65307)
		game->destroy(game);
	else if (keycode == KEY_W)
		game->player->up = 1;
	else if (keycode == KEY_S)
		game->player->down = 1;
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		game->player->right = 1;
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		game->player->left = 1;
	else
		printf("Le keycode est pas set keycode = %d\n", keycode);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->player->up = 0;
	else if (keycode == KEY_S)
		game->player->down = 0;
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		game->player->right = 0;
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		game->player->left = 0;
	return (0);
}

void	identify_move(t_game *game)
{
	if (game->player->up == 1)
		game->player->velocity.y = game->player->speed * -1;
	if (game->player->down == 1)
		game->player->velocity.y = game->player->speed;
	if (game->player->right == 1)
		game->player->velocity.x = game->player->speed;
	if (game->player->up == 1)
		game->player->velocity.x = game->player->speed * -1;
}
