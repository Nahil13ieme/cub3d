/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:16:35 by nbenhami          #+#    #+#             */
/*   Updated: 2025/06/04 12:20:11 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "cub3d.h"

typedef struct s_file_manager
{
	char	*wall_north;
	char	*wall_south;
	char	*wall_east;
	char	*wall_west;
	char	*cell;
	char	*floor;
}	t_file_manager;
typedef struct s_map
{
	int				width;
	int				height;
	char			dir;
	char			**tiles;
	char			**tab;
	t_vector2d		start;
	t_file_manager	*files;
	void			(*destroy)(struct s_map *map);
	//objects if any
}	t_map;

void	destroy_map(t_map *map);
t_map	*new_map();

#endif /* MAP_H */
