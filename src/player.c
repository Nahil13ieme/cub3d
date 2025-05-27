/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:15:02 by nbenhami          #+#    #+#             */
/*   Updated: 2025/05/27 14:35:42 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/player.h"

t_player	*ft_init_player(t_game *game)
{
	int			i;
	int			j;
	t_player	*player;
	char		**map;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	map = game->map->tiles;
	player->velocity.x = 0;
	player->velocity.y = 0;
	i = 0;
	player->destroy = destroy_player;
	player->fov = 60;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				player->pos.x = j + 0.5f;
				player->pos.y = i + 0.5f;
				game->map->start = vector2d(j, i);
				player->dir = vector2d(0, -1);
				return (player);
			}
			j++;
		}
		i++;
	}
	return (printf("No Starting Pos\n"), NULL);
}

void	move_player(t_game	*game)
{
	t_vector2d	new_pos;
	float		box_size;

	box_size = 0.1f;
	new_pos.x = game->player->pos.x + game->player->velocity.x * 0.5;
	if (new_pos.x - box_size >= 0 && new_pos.x + box_size < game->map->width
		&& game->map->tiles[(int)(game->player->pos.y - box_size)][(int)
			(new_pos.x - box_size)] != '1'
		&& game->map->tiles[(int)(game->player->pos.y + box_size)][(int)
			(new_pos.x - box_size)] != '1'
		&& game->map->tiles[(int)(game->player->pos.y - box_size)][(int)
			(new_pos.x + box_size)] != '1'
		&& game->map->tiles[(int)(game->player->pos.y + box_size)][(int)
			(new_pos.x + box_size)] != '1')
		game->player->pos.x = new_pos.x;
	// Attempt to move along the y-axis
	new_pos.y = game->player->pos.y + game->player->velocity.y * 0.5;
	if (new_pos.y - box_size >= 0 && new_pos.y + box_size < game->map->height
		&& game->map->tiles[(int)(new_pos.y - box_size)]
			[(int)(game->player->pos.x - box_size)] != '1'
		&& game->map->tiles[(int)(new_pos.y + box_size)]
			[(int)(game->player->pos.x - box_size)] != '1'
		&& game->map->tiles[(int)(new_pos.y - box_size)]
			[(int)(game->player->pos.x + box_size)] != '1'
		&& game->map->tiles[(int)(new_pos.y + box_size)]
			[(int)(game->player->pos.x + box_size)] != '1')
		game->player->pos.y = new_pos.y;
}

void	destroy_player(t_player *player)
{
	t_player	*fplayer;

	fplayer = (t_player *)player;
	free(fplayer);
}
