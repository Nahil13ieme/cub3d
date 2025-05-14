/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:15:02 by nbenhami          #+#    #+#             */
/*   Updated: 2025/05/14 16:47:50 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/player.h"

t_player	*ft_init_player(t_game *game)
{
	int			i;
	int			j;
	t_player	*player;
	char		**map;

	player = NULL;
	if (!player)
		return (NULL);
	map = game->map->tiles;
	if (map == NULL)
		return (free(player), NULL);
	player->velocity.x = 0;
	player->velocity.y = 0;
	i = 0;
	player->destroy = destroy_player;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
			{
				player->pos.x = j;
				player->pos.y = i;
				game->map->start = vector2d(j, i);
				player->dir = vector2d(0, -1);
				return (player);
			}
			j++;
		}
		i++;
	}
	return (printf("Error\nNo Starting Pos\n"), NULL);
}

void	move_player(t_game	*game)
{
	t_vector2d	pos;

	pos.x = game->player->pos.x + game->player->velocity.x;
	pos.y = game->player->pos.y + game->player->velocity.y;
	game->player->pos = pos;
}

void	destroy_player(t_player *player)
{
	t_player	*fplayer;

	fplayer = (t_player *)player;
	free(fplayer);
}
