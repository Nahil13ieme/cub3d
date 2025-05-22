/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:28:03 by tle-saut          #+#    #+#             */
/*   Updated: 2025/05/22 14:42:08 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_player_box(t_game	*game)
{
	float		x;
	float		y;

	x = game->player->pos.x;
	y = game->player->pos.y;

	game->player->box.pos = vector2d(game->player->pos.x, game->player->pos.y);
	game->player->box.size = vector2d(SIZE,SIZE);

}

#include <math.h>

int	check_collisions(t_bbox player, int rows, int cols)
{
	if (player.pos.x < 1 || player.pos.y < 1 || (player.pos.x + 1) > cols - 1 || (player.pos.y + 1) > rows - 1)
		return (1);
	return (0);
}



