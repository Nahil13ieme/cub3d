/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:28:03 by tle-saut          #+#    #+#             */
/*   Updated: 2025/05/27 14:00:17 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <math.h>

void	set_player_box(t_player *player)
{
	player->box.pos = vector2d(player->pos.x, player->pos.y);
	player->box.size = vector2d(SIZE, SIZE);
}

int	check_collisions(t_bbox player, int rows, int cols)
{
	if (player.pos.x < 1 || player.pos.y < 1 || (player.pos.x) > cols - 1
		|| (player.pos.y) > rows)
		return (1);
	return (0);
}
