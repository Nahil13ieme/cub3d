/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:16:35 by nbenhami          #+#    #+#             */
/*   Updated: 2025/05/14 12:50:36 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "cub3d.h"

typedef struct s_map
{
	int			width;
	int			height;
	char		dir;
	char		**tiles;
	t_vector2d	start;
	void		(*destroy)(struct s_map *map);
	//objects if any
}	t_map;

void	destroy_map(t_map *map);
t_map	*new_map();

#endif /* MAP_H */