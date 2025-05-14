/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:10:34 by nbenhami          #+#    #+#             */
/*   Updated: 2025/05/14 12:42:08 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "cub3d.h"

typedef struct s_vector2d	t_vector2d;
typedef struct s_game		t_game;

typedef struct s_player
{
	float		hp;
	float		speed;
	float		fov;
	t_vector2d	velocity;
	t_vector2d	dir;
	t_vector2d	pos;
	void		(*destroy)(struct s_player *player);
}	t_player;

t_player	*ft_init_player(t_game *game);
void		move_player(t_game	*game);
void		destroy_player(t_player *player);

#endif /* PLAYER_H */