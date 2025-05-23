/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:18:42 by nbenhami          #+#    #+#             */
/*   Updated: 2025/05/18 16:17:39 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "cub3d.h"

typedef struct s_game		t_game;
typedef struct s_texture	t_texture;
typedef struct s_debug
{
	void			*mlx;
	void			*win;
	t_game			*game;
	void			(*destroy)(struct s_debug **debug);
}	t_debug;

t_debug	*new_debug(t_game *game);
int		debug_loop(t_debug *debug);
int		debug_keyhook(int keycode, t_debug *debug);
void	destroy_debug(t_debug **debug);
long	get_time_microseconds(void);
void	raycast_cone(t_game *game, t_texture *t);

#endif /* DEBUG_H */