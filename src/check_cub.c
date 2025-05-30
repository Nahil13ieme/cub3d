/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:03:52 by tle-saut          #+#    #+#             */
/*   Updated: 2025/05/30 14:07:15 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
		map->tiles[k] = tab[i];
		k++;
		i++;
	}
	map->tiles[k] = 0;
}


void	set_texture(char **text, char *str)
{
	while (*str && *str != '.')
		str++;
	*text = str;
}

int	check_cub(t_game *game, t_map *map)
{
	if (map->tab[0][0]!= 'N'
			|| map->tab[1][0]!= 'S'
			|| map->tab[2][0]!= 'W'
			|| map->tab[3][0]!= 'E'
			|| map->tab[4][0]!= 'F'
			|| map->tab[5][0]!= 'C')
			{
				return (printf("Error\n From .cub file"), 1);
			}
	copy_map(map, map->tab, 6);
	set_texture(&game->pathn, map->tab[0]);
	set_texture(&game->paths, map->tab[1]);
	set_texture(&game->pathw, map->tab[2]);
	set_texture(&game->pathe, map->tab[3]);
	game->tex_man->floor = map->tab[5];
	game->tex_man->cell = map->tab[6];

	return (0);
}
