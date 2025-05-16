/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:15:26 by nbenhami          #+#    #+#             */
/*   Updated: 2025/05/15 17:16:08 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

t_map	*new_map(void)
{
	t_map	*map;
	int		i;
	int		j;

	map = malloc(sizeof(t_map));
	map->tiles = malloc(sizeof(char *) * 5);
	if (!map->tiles)
		return (NULL);
	i = 0;
	while (i < 5)
	{
		map->tiles[i] = malloc(sizeof(char) * 5);
		j = -1;
		while (++j < 5)
		{
			if (i == 0 || j == 0 || i == 4 || j == 4)
				map->tiles[i][j] = '1';
			else if (i == 3 && j == 3)
				map->tiles[i][j] = 'P';
			else
				map->tiles[i][j] = '0';
		}
		i++;
	}
	return (map);
}

void	destroy_map(t_map *map)
{
	free(map->tiles);
	free(map);
}

int	parsing(char **tiles)
{
	int	i;
	int	j;

	i = 0;
	while (tiles[i])
	{
		j = 0;
		while (tiles[i][j])
			j++;
	}
	return (0);
}
