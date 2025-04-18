/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:46:57 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/16 21:25:59 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_file_name(char *av, int len)
{
	int		i;
	int		j;
	char	*comp;

	comp = ".cub";
	i = 3;
	j = 0;
	len--;
	while (j < 4)
	{
		if (av[len - j] != comp[i - j])
			return (FALSE);
		j++;
	}
	return (TRUE);
}

int	check_file(char *av)
{
	int	fd;
	int	len;

	len = ft_strlen(av);
	if (len <= 4 || check_file_name(av, len) == FALSE)
		return (printf("Couldnt open file, waiting for a .cub format"), FALSE);
	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (printf("Couldnt open file %s\n", av), FALSE);
	return (TRUE);
}
