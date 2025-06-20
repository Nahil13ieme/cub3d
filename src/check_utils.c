/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:46:26 by tle-saut          #+#    #+#             */
/*   Updated: 2025/06/16 13:51:18 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_texture(char **text, char *str)
{
	while (*str && *str != ' ')
		str++;
	str++;
	*text = ft_strdup(str);
}

int	init_tex_man(t_game *game)
{
	game->tex_man = malloc(sizeof(t_texture_manager));
	if (!game->tex_man)
		return (1);
	game->tex_man->wall_east = NULL;
	game->tex_man->wall_north = NULL;
	game->tex_man->wall_west = NULL;
	game->tex_man->wall_south = NULL;
	game->tex_man->cell = NULL;
	game->tex_man->floor = NULL;
	return (0);
}

void	copy_map(t_map *map, char **tab, int i)
{
	int	k;
	int	l;

	l = i;
	k = 0;
	while (tab[l])
		l++;
	map->tiles = malloc(sizeof(char **) * (l - i + 1));
	while (tab[i])
	{
		map->tiles[k] = ft_strdup(tab[i]);
		k++;
		i++;
	}
	map->tiles[k] = 0;
}
