/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:24:00 by tle-saut          #+#    #+#             */
/*   Updated: 2025/06/05 14:44:23 by tle-saut         ###   ########.fr       */
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
