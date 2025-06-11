/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:24:00 by tle-saut          #+#    #+#             */
/*   Updated: 2025/06/11 23:31:12 by tle-saut         ###   ########.fr       */
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

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}


int	check_char(char c)
{
	if (c == '1' || c == '0')
		return (0);
	else if (c == 'N' || c == 'S')
		return (0);
	else if (c == 'W' || c == 'E')
		return (0);
	else
		return (1);
}
int	check_search(char **map, int lock, int i)
{
	int	j;

	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			while (map[i][j] == ' ')
				j++;
			if (check_char(map[i][j]) && map[i][j])
				return (printf("Error\nCharacter not alowed in map : '%c'\n",
						 map[i][j]), 1);
			if ((map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
				|| map[i][j] == 'E') && lock == 0  && map[i][j])
				lock = 1;
			else if ((map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
				|| map[i][j] == 'E') && lock == 1  && map[i][j])
				return (printf("Error\nToo many spawn point\n"), 1);
			if (map[i][j])
				j++;
		}
		i++;
	}
	return (0);
}
