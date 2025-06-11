/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:15:02 by nbenhami          #+#    #+#             */
/*   Updated: 2025/06/11 16:46:20 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/player.h"

static t_player	*set_player_dir(t_game *g, t_player *p, int i, int j)
{
	p->velocity = vector2d(0, 0);
	p->pos = vector2d(j + 0.5f, i + 0.5f);
	g->map->start = vector2d(j, i);
	p->dir = vector2d(0, -1);
	return (p);
}

t_player	*ft_init_player(t_game *game)
{
	int			i;
	int			j;
	t_player	*player;
	char		**map;
	char		c;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	map = game->map->tiles;
	player->destroy = destroy_player;
	player->fov = 60;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			c = map[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				return (set_player_dir(game, player, i, j));
		}
	}
	printf("No Starting Pos\n");
	return (NULL);
}

static int	is_walkable_x(t_game *g, t_vector2d pos, float box)
{
	if (pos.x - box < 0 || pos.x + box >= g->map->width)
		return (0);
	if (g->map->tiles[(int)(g->player->pos.y - box)]
		[(int)(pos.x - box)] == '1')
		return (0);
	if (g->map->tiles[(int)(g->player->pos.y + box)]
		[(int)(pos.x - box)] == '1')
		return (0);
	if (g->map->tiles[(int)(g->player->pos.y - box)]
		[(int)(pos.x + box)] == '1')
		return (0);
	if (g->map->tiles[(int)(g->player->pos.y + box)]
		[(int)(pos.x + box)] == '1')
		return (0);
	return (1);
}

static int	is_walkable_y(t_game *g, t_vector2d pos, float box)
{
	if (pos.y - box < 0 || pos.y + box >= g->map->height)
		return (0);
	if (g->map->tiles[(int)(pos.y - box)]
		[(int)(g->player->pos.x - box)] == '1')
		return (0);
	if (g->map->tiles[(int)(pos.y + box)]
		[(int)(g->player->pos.x - box)] == '1')
		return (0);
	if (g->map->tiles[(int)(pos.y - box)]
		[(int)(g->player->pos.x + box)] == '1')
		return (0);
	if (g->map->tiles[(int)(pos.y + box)]
		[(int)(g->player->pos.x + box)] == '1')
		return (0);
	return (1);
}

void	move_player(t_game *game)
{
	t_vector2d	new_pos;
	float		box;

	box = 0.1f;
	new_pos.x = game->player->pos.x + game->player->velocity.x * 0.5;
	if (is_walkable_x(game, new_pos, box))
		game->player->pos.x = new_pos.x;
	new_pos.y = game->player->pos.y + game->player->velocity.y * 0.5;
	if (is_walkable_y(game, new_pos, box))
		game->player->pos.y = new_pos.y;
}
