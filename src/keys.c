/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:22:24 by tle-saut          #+#    #+#             */
/*   Updated: 2025/05/16 16:05:24 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int ft_key_pressed(int keycode, void *param)
{
	t_game *game = (t_game *)param;

	if (keycode == 65307)
		game->destroy(game);
	else if (keycode == KEY_W)
		game->player->up = 1;
	else if (keycode == KEY_S)
		game->player->down = 1;
	else if (keycode == KEY_D)
		game->player->right = 1;
	else if (keycode == KEY_A)
		game->player->left = 1;
	else if (keycode == KEY_MAJ)
		game->player->maj = 1;
	else
		printf("Le keycode est pas set keycode = %d\n", keycode);

	return (0);
}

int ft_key_release(int keycode, void *param)
{
	t_game *game = (t_game *)param;

	if (keycode == KEY_W)
		game->player->up = 0;
	if (keycode == KEY_S)
		game->player->down = 0;
	if (keycode == KEY_D)
		game->player->right = 0;
	if (keycode == KEY_A)
		game->player->left = 0;
	if (keycode == KEY_MAJ)
		game->player->maj = 0;
	return (0);
}

void identify_move(t_game *game)
{
	
	if (game->player->up == 1)
		game->player->velocity.y = -game->player->speed;
	else if (game->player->down == 1)
		game->player->velocity.y = game->player->speed;
	else
		game->player->velocity.y = 0;

	if (game->player->right == 1)
		game->player->velocity.x = game->player->speed;
	else if (game->player->left == 1)
		game->player->velocity.x = -game->player->speed;
	else
		game->player->velocity.x = 0;
	
	if (game->player->maj == 1)
		game->player->speed = SPEED * 2;
	else 
		game->player->speed = SPEED;
}


