/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:18:42 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/17 13:30:19 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "cub3d.h"

typedef struct s_game	t_game;

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

#endif /* DEBUG_H */