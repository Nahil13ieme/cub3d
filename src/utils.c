/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:24:00 by tle-saut          #+#    #+#             */
/*   Updated: 2025/06/16 11:05:16 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
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
	if (game->tex_man->wall_east == NULL || game->tex_man->wall_north == NULL
		|| game->tex_man->wall_south == NULL
		|| game->tex_man->wall_west == NULL)
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
