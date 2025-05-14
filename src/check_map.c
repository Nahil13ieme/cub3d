/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:56:34 by tle-saut          #+#    #+#             */
/*   Updated: 2025/05/14 17:11:42 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*ft_strjoinfree(char **s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*dest;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * (ft_strlen(*s1) + ft_strlen(s2) + 1));
	if (!dest)
		return (NULL);
	while ((*s1)[i])
	{
		dest[i] = (*s1)[i];
		i++;
	}
	while (s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	if (*s1 != NULL)
		free(*s1);
	return (dest);
}
int	ft_tablen(char	**tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i - 1);
}

char	**ft_init_tab(int fd)
{
	int		a;
	char	buffer[BUFFER_SIZE + 1];
	char	**tab;
	char	*line;

	line = NULL;
	tab = NULL;
	a = 0;
	while (1)
	{
		a = read(fd, buffer, BUFFER_SIZE);
		if (a < 1)
			break ;
		buffer[a] = '\0';
		if (line == NULL)
			line = ft_strdup(buffer);
		else
			line = ft_strjoinfree(&line, buffer);
	}
	tab = ft_split(line, '\n');
	free(line);
	return (tab);
}

void	ft_print_tab(char **tab)
{
	int i;

	i = 0;
	
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

t_map	*ft_init_map(char *path)
{
	int		fd;
	t_map	*map;
	int	i;

	map = malloc(sizeof(t_map));
	map->destroy = destroy_map;
	i = 0;
	map->width = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nfile reading\n"), NULL);
	map->tiles = ft_init_tab(fd);
	close(fd);
	if(map->tiles == NULL)
		return(printf("Error\nmap is not load"), NULL);
	map->height = ft_tablen(map->tiles);
	while (map->tiles[i])
	{
		if (map->width < ft_strlen(map->tiles[i]))
		map->width = ft_strlen(map->tiles[i]);
		i++;
	}
	printf("height : %d\nwidth : %d\n", map->height, map->width);
	if (check_border(*map) == 1)
		return (printf("Error\nMap Invalide\n"), NULL);
	return (map);
}
