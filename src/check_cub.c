/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:03:52 by tle-saut          #+#    #+#             */
/*   Updated: 2025/06/16 11:06:08 by nbenhami         ###   ########.fr       */
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

static void	free_map_tiles(t_map *map)
{
	int	i;

	if (!map->tiles)
		return ;
	i = 0;
	while (map->tiles[i])
	{
		free(map->tiles[i]);
		i++;
	}
	free(map->tiles);
	map->tiles = NULL;
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static int	is_number_between_0_255(char *s)
{
	int n = 0;

	if (!s || !*s)
		return (0);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		n = n * 10 + (*s - '0');
		if (n > 255)
			return (0);
		s++;
	}
	return (1);
}

static int	check_color(char *str)
{
	char	**split;
	int		i;

	if (!str || (str[0] != 'F' && str[0] != 'C') || str[1] != ' ')
		return (1);
	split = ft_split(str + 2, ',');
	if (!split)
		return (1);
	i = 0;
	while (split[i])
		i++;
	if (i != 3)
		return (free_split(split), 1);
	if (!is_number_between_0_255(split[0])
		|| !is_number_between_0_255(split[1])
		|| !is_number_between_0_255(split[2]))
		return (free_split(split), 1);
	free_split(split);
	return (0);
}

int	check_cub(t_game *game, t_map *map)
{
	if (!map->tab || !map->tab[0] || map->tab[0][0] != 'N'
			|| map->tab[1][0] != 'S'
			|| map->tab[2][0] != 'W'
			|| map->tab[3][0] != 'E'
			|| map->tab[5][0] != 'F'
			|| map->tab[6][0] != 'C')
	{
		return (printf("Error\nFrom .cub file\n"), 1);
	}
	copy_map(map, map->tab, 8);
	if (init_tex_man(game) == 1)
		return (printf("Error\nInit From texture\n"), 1);
	set_texture(&game->pathn, map->tab[0]);
	set_texture(&game->paths, map->tab[1]);
	set_texture(&game->pathw, map->tab[2]);
	set_texture(&game->pathe, map->tab[3]);
	load_textures(game);
	if (ft_strlen(map->tab[5]) < 5 || ft_strlen(map->tab[6]) < 5
		|| check_error_parsing(game) == 1)
		return (free_map_tiles(map), destroy_img(game, 1), 1);
	if (check_color(map->tab[5]) == 1
		|| check_color(map->tab[6]) == 1)
		return (free_map_tiles(map), destroy_img(game, 1), 1);
	game->tex_man->floor = ft_strdup(map->tab[5] + 2);
	game->tex_man->cell = ft_strdup(map->tab[6] + 2);
	return (0);
}
