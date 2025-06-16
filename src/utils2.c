/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 00:00:26 by tle-saut          #+#    #+#             */
/*   Updated: 2025/06/16 13:29:05 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
				|| map[i][j] == 'E') && lock == 0 && map[i][j])
				lock = 1;
			else if ((map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
				|| map[i][j] == 'E') && lock == 1 && map[i][j])
				return (printf("Error\nToo many spawn point\n"), 1);
			if (map[i][j])
				j++;
		}
		i++;
	}
	return (0);
}

void	draw_buffer(t_game *game)
{
	draw_floor(game);
	draw_walls(game);
}
