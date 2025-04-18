/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:10:34 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/17 12:16:56 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "cub3d.h"

typedef struct s_vector2d	t_vector2d;

typedef struct s_player
{
	float		hp;
	float		speed;
	float		fov;
	t_vector2d	pos;
	void		(*destroy)(struct s_player *player);
	// sprite
}	t_player;

void	destroy_player(t_player *player);

#endif /* PLAYER_H */