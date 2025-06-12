/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_border.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:03:53 by tle-saut          #+#    #+#             */
/*   Updated: 2025/06/12 15:10:24 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_horizon(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(str) - 1;
	while (str[i] == ' ' && str[i])
		i++;
	if (str[i] == 0)
		return (0);
	if (str[i] != '1')
		return (1);
	while (str[j] == ' ')
		j--;
	if (str[j] != '1')
		return (1);
	return (0);
}

static int	check_top_or_bottom(char **tab, int j, int from_bottom)
{
	int	i;
	int	len;

	len = ft_tablen(tab);
	if (from_bottom)
		i = len;
	else
		i = 0;
	while ((from_bottom && i >= 0) || (!from_bottom && i < len))
	{
		if (tab[i][j] != ' ' && tab[i][j] != '\n')
		{
			if (tab[i][j] != '1')
			{
				printf("ligne %d\ncolonne %d\n", i, j);
				return (1);
			}
			break ;
		}
		if (from_bottom)
			i--;
		else
			i++;
	}
	return (0);
}

int	check_verti(char **tab)
{
	int	j;

	j = 0;
	while (j < (int)ft_strlen(tab[0]))
	{
		if (check_top_or_bottom(tab, j, 0))
			return (1);
		if (check_top_or_bottom(tab, j, 1))
			return (1);
		j++;
	}
	return (0);
}

int	check_border(t_map map)
{
	int	i;

	i = 0;
	while (i < ft_tablen(map.tiles))
	{
		if (check_horizon(map.tiles[i]) == 1)
			return (printf("horizontale\n"), 1);
		i++;
	}
	if (check_verti(map.tiles) == 1)
		return (printf("verticale\n"), 1);
	return (0);
}
