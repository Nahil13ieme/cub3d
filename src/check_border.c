/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_border.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:03:53 by tle-saut          #+#    #+#             */
/*   Updated: 2025/05/15 17:13:51 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_horizon(char *str)
{
	int	first;
	int	last;
	int	i;

	i = 0;
	first = 0;
	last = 0;
	while (str[i])
	{
		if (first == 1)
			if (str[i] != '1' && str[i - 1] == '1')
				last = 1;
		if (str[i + 1] == 0 && str[i] == '1')
			last = 1;
		if (str[i] == '1' && first == 0)
			first = 1;
		i++;
	}
	if (first == 1 && last == 1)
		return (0);
	return (1);
}

int	check_border(t_map map)
{
	int	i;

	i = 0;
	while (map.tiles[i])
	{
		if (check_horizon(map.tiles[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}
