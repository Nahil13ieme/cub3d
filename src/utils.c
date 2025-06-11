/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:24:00 by tle-saut          #+#    #+#             */
/*   Updated: 2025/06/11 16:52:21 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_tablen(char	**tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i - 1);
}

void	set_size_map(t_map *map)
{
	int		i;

	map->height = ft_tablen(map->tiles);
	i = 0;
	while (map->tiles[i])
	{
		if (map->width < ft_strlen(map->tiles[i]))
			map->width = ft_strlen(map->tiles[i]);
		i++;
	}
}

int	check_error_parsing(t_game *game)
{
	if (game->tex_man->wall_east == NULL || game->tex_man->wall_east == NULL
		|| game->tex_man->wall_east == NULL
		|| game->tex_man->wall_east == NULL)
		{
			return (1);
		}
	return (0);
}

int	flood_fill(int x, int y, char **map, int lock)
{
	if ((x < 1 || x > ft_strlen(map[0])) && (y < 1 || y > ft_tablen(map)))
		return (0);
	if ((map[y][x] == 'N' || map[y][x] == 'E' || map[y][x] == 'S'
		|| map[y][x] == 'W') && lock == 1)
			return (printf("Error\nToo many spawn point\n"), 1);
	else if ((map[y][x] == 'N' || map[y][x] == 'E' || map[y][x] == 'S'
		|| map[y][x] == 'W') && lock == 0)
			lock = 1;
	else if (map[y][x] != 1 && map[y][x] != 0)
		return (1);
	else if (map[y][x] == 1 && map[y][x] == 0)
		{
			if (flood_fill(x + 1, y, map, lock) == 1
				&& flood_fill(x - 1, y, map, lock) == 1
				&& flood_fill(x, y + 1, map, lock) == 1
				&& flood_fill(x, y - 1 , map, lock) == 1)
					return (printf("Error\nCharacter not alowed in map\n"), 1);
		}
	return (0);
}
