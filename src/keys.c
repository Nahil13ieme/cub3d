/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:22:24 by tle-saut          #+#    #+#             */
/*   Updated: 2025/05/24 04:16:03 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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


