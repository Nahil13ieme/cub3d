/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:15:02 by nbenhami          #+#    #+#             */
/*   Updated: 2025/05/24 03:56:12 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/player.h"

static void	set_player_dir(t_player *player, char c)
{
	if (c == 'N')
		player->dir = vector2d(0, -1);
	else if (c == 'S')
		player->dir = vector2d(0, 1);
	else if (c == 'E')
		player->dir = vector2d(-1, 0);
	else if (c == 'Z')
		player->dir = vector2d(1, 0);
}

static t_player	*init_player_value(t_player *player)
{
	player->down = 0;
	player->up = 0;
	player->left = 0;
	player->right = 0;
	player->maj = 0;
	player->velocity.x = 0;
	player->velocity.y = 0;
	player->destroy = destroy_player;
	player->speed = SPEED;
	return (player);
}

t_player	*ft_init_player(t_game *game)
{
	int			i;
	int			j;
	t_player	*player;
	char		**map;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player = init_player_value(player);
	set_player_box(player);
	map = game->map->tiles;
	if (map == NULL)
		return (free(player), NULL);
	i = 0;
	player->destroy = destroy_player;
	player->fov = 60;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
			{
				player->pos.x = (float)j + 0.5f;
				player->pos.y = (float)i + 0.5f;
				game->map->start = vector2d(j, i);
				set_player_dir(player, map[i][j]);
				return (player);
			}
			j++;
		}
		i++;
	}
	return (printf("Error\nNo Starting Pos\n"), NULL);
}

void	move_player(t_game *game)
{
	t_player *player = game->player;
	t_bbox future;

	// Simule la bbox future AVANT de déplacer le joueur
	future = player->box;
	if ((player->up == 1 && player->right == 1) ||
		(player->up == 1 && player->left == 1) ||
		(player->down == 1 && player->right == 1) ||
		(player->down == 1 && player->left == 1))
	{
		future.pos.x += player->velocity.x / 1.5;
		future.pos.y += player->velocity.y / 1.5;
	}
	if (check_collisions(future, game->map->height, game->map->width) == 0)
	{
		player->pos.x += player->velocity.x;
		player->pos.y += player->velocity.y;
	}
	set_player_box(game->player);
}


void	destroy_player(t_player *player)
{
	free(player);
}
