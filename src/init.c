/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:13:49 by tle-saut          #+#    #+#             */
/*   Updated: 2025/05/13 09:54:31 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_set_dir_player(char c, t_player *player)
{
	if (c == 'N')
		player->dir = 90.0;
	if (c == 'E')
		player->dir = 180.0;
	if (c == 'S')
		player->dir = 270.0;
	if (c == 'W')
		player->dir = 0.0;
}

t_player	*ft_init_player(char **map)
{
	int	i;
	int	j;
	t_player	*player;

	player = malloc(sizeof(t_player));
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
			{
				player->pos.x = j;
				player->pos.y = i;
				ft_set_dir_player(map[i][j], player);
				printf("pos x : %f\npos y : %f\ndir : %f\n", player->pos.x, player->pos.y, player->dir);
				return (player);
			}
			j++;
		}
		i++;
	}
	return (printf("No Starting Pos\n"), NULL);
}
