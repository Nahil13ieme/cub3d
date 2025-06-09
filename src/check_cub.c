/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:03:52 by tle-saut          #+#    #+#             */
/*   Updated: 2025/06/09 16:17:41 by tle-saut         ###   ########.fr       */
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
		map->tiles[k] = ft_strdup(tab[i]);
		k++;
		i++;
	}
	map->tiles[k] = 0;
}

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
	return (0);
}

int	check_cub(t_game *game, t_map *map)
{
	if (map->tab[0][0] != 'N'
			|| map->tab[1][0] != 'S'
			|| map->tab[2][0] != 'W'
			|| map->tab[3][0] != 'E'
			|| map->tab[4][0] != 'F'
			|| map->tab[5][0] != 'C')
	{
		return (printf("Error\nFrom .cub file\n"), 1);
	}
	copy_map(map, map->tab, 6);
	if (init_tex_man(game) == 1)
		return (printf("Error\nFrom texture\n"), 1);
	set_texture(&game->pathn, map->tab[0]);
	set_texture(&game->paths, map->tab[1]);
	set_texture(&game->pathw, map->tab[2]);
	set_texture(&game->pathe, map->tab[3]);
	load_textures(game);
	if ((int)ft_strlen(map->tab[4]) < 5 || (int)ft_strlen(map->tab[5]) < 5
		|| check_error_parsing(game) == 1)
		return (printf("Error\nFrom texture\n"), 1);
	game->tex_man->floor = ft_substr(map->tab[4], 2, ft_strlen(map->tab[4]));
	game->tex_man->cell = ft_substr(map->tab[5], 2, ft_strlen(map->tab[5]));
	return (0);
}


