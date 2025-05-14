/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_border.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:03:53 by tle-saut          #+#    #+#             */
/*   Updated: 2025/05/14 15:04:09 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_horizon(char *str)
{
	int	i;
	int	j;
	
	i = 0;
	j = ft_strlen(str) - 1;
	while (str[i] == ' ')
		i++;
	if (str[i] != '1')
		return (1);
	while (str[j] == ' ')
		j--;
	if (str[j] != '1')
		return (1);
	return (0);
}

int	check_border(t_map map)
{
	int	i;

	i = 0;
	while (map.tiles[i])
	{
		if(check_horizon(map.tiles[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}
