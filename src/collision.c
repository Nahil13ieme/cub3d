/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:28:03 by tle-saut          #+#    #+#             */
/*   Updated: 2025/05/15 15:37:08 by tle-saut         ###   ########.fr       */
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

int check_collision(t_bbox a, t_bbox b)
{
	if (a.pos.x < b.pos.x + b.size.x &&
		a.pos.x + a.size.x > b.pos.x &&
		a.pos.y < b.pos.y + b.size.y &&
		a.pos.y + a.size.y > b.pos.y)
		return (1); // collision
	return (0);     // pas de collision
}
void check_collisions(t_bbox player, char **map, int rows, int cols)
{
	t_bbox	wall;
	int		y;
	int		x;
	
	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			if (map[y][x] == '1') // mur
			{
				wall.pos.x = x * SIZE;
				wall.pos.y = y * SIZE;
				wall.size.x = SIZE;
				wall.size.y = SIZE;
				if (is_colliding(player, wall))
				{
					printf("💥 Collision détectée avec mur en (%d, %d)\n", x, y);
				}
			}
			x++;
		}
		y++;
	}
}


