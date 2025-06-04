/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:15:26 by nbenhami          #+#    #+#             */
/*   Updated: 2025/06/04 12:09:08 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

t_map	*new_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	return (map);
}

void	destroy_map(t_map *map)
{
	if (!map)
		return;
	if (map->tiles)
	{
		int	i;

		i = 0;
		while (i < map->height + 1)
		{
			if (map->tiles[i])
				free(map->tiles[i]);
			i++;
		}
	}
	free(map->tiles);
	free(map->tab);
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
