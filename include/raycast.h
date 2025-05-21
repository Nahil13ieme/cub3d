/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:24:55 by nbenhami          #+#    #+#             */
/*   Updated: 2025/05/18 15:31:50 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "cub3d.h"

typedef struct s_texture	t_texture;

typedef struct s_raycast
{
	t_vector2d	step;
	t_vector2d	side_dist;
	t_vector2d	delta_dist;
	t_vector2d	pos;
	int			map_x;
	int			map_y;
}	t_raycast;

void		draw_pixel(t_texture *t, int x, int y, int color);
void		draw_line(t_texture *t, t_vector2d start, t_vector2d end, int color);
t_vector2d	raycast_to_wall(t_game *game, t_vector2d origin, t_vector2d dir);

#endif // RAYCAST_H
