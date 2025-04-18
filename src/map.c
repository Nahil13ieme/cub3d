/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:15:26 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/17 13:57:13 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	destroy_map(t_map *map)
{
	(void)map;
}

int		parsing(char **tiles)
{
	int	i;
	int	j;

	i = 0;
	while(tiles[i])
	{
		j = 0;
		while (tiles[i][j])
		{
			if (i == 0 && tiles[i][j])
			j++;
		}
	}
	return (0);
}