/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:56:34 by tle-saut          #+#    #+#             */
/*   Updated: 2025/05/12 13:10:45 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_check_after_flood(char **map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1')
				return (ft_putstr_fd("Error\nPath is invalid\n", 2), 1);
			j++;
		}
		printf("\n");
		i++;
	}
	return (0);
}

int	ft_check_border(t_map *map)
{

}

// char	**ft_flood_path(char **map, int ystart, int xstart, t_all *all)
// {
// 	if (map[ystart][xstart] == '1')
// 		return (0);
// 	map[ystart][xstart] = '1';
// 	all->line = ft_tablen(map);
// 	all->column = ft_strlen(map[0]);
// 	if (ystart + 1 < all->line && map[ystart + 1][xstart] != '1')
// 		ft_flood_path(map, ystart + 1, xstart, all);
// 	if (ystart - 1 > 0 && map[ystart - 1][xstart] != '1')
// 		ft_flood_path(map, ystart - 1, xstart, all);
// 	if (xstart + 1 < all->column - 1 && map[ystart][xstart + 1] != '1')
// 		ft_flood_path(map, ystart, xstart + 1, all);
// 	if (xstart - 1 > 0 && map[ystart][xstart - 1] != '1')
// 		ft_flood_path(map, ystart, xstart - 1, all);
// 	return (map);
// }

char	**ft_copy_map(char **map, char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error from file reading\n", 2), NULL);
	map = NULL;
	map = ft_init_tab(fd);
	close(fd);
	return (map);
}

void	ft_free_tab(char **tab)
{
	int	i;
	int	len;

	i = 0;
	len = ft_tablen(tab);
	while (i <= len)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

// char	**ft_init_tab(int fd)
// {
// 	int		a;
// 	char	buffer[BUFFER_SIZE + 1];
// 	char	**tab;
// 	char	*line;

// 	line = NULL;
// 	while (1)
// 	{
// 		a = read(fd, buffer, BUFFER_SIZE);
// 		if (a < 1)
// 			break ;
// 		if (line == NULL)
// 			line = ft_strdup(buffer);
// 		else
// 			line = ft_strjoinfree(&line, buffer);
// 	}
// 	tab = ft_split(line, '\n');
// 	free(line);
// 	return (tab);
// }

// int	ft_init_map(t_all *map, char *path)
// {
// 	int		fd;

// 	fd = open(path, O_RDONLY);
// 	if (fd == -1)
// 		return (ft_putstr_fd("Error from file reading\n", 2), 1);
// 	map->map = ft_init_tab(fd);
// 	map->player = 0;
// 	map->exit = 0;
// 	map->collectible = 0;
// 	map->column = 0;
// 	map->line = 0;
// 	close(fd);
// 	return (0);
// }

// int	ft_give_all_nbpoint(t_all *map)
// {
// 	int	i;
// 	int	j;

// 	ft_get_enemy_pos(map);
// 	i = 0;
// 	map->line = ft_tablen(map->map);
// 	map->column = ft_strlen(map->map[i]);
// 	while (map->map[i])
// 	{
// 		if ((int)ft_strlen(map->map[i]) != map->column)
// 			return (ft_putstr_fd("Line is not the same size\n", 2), 1);
// 		j = 0;
// 		while (map->map[i][j])
// 		{
// 			if (map->map[i][j] == 'P')
// 				map->player += 1;
// 			else if (map->map[i][j] == 'E')
// 				map->exit += 1;
// 			else if (map->map[i][j] == 'C')
// 				map->collectible += 1;
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// int	ft_give_start_pos(t_all *game)
// {
// 	while (game->map[game->ystart])
// 	{
// 		game->xstart = 0;
// 		while (game->map[game->ystart][game->xstart])
// 		{
// 			if (game->map[game->ystart][game->xstart] == 'P')
// 				return (0);
// 			game->xstart++;
// 		}
// 		game->ystart++;
// 	}
// 	return (ft_putstr_fd("Starting POS Missing\n", 2), 1);
// }
