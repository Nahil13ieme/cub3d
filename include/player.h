/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:10:34 by nbenhami          #+#    #+#             */
/*   Updated: 2025/06/05 14:32:54 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "cub3d.h"

# define SPEED 0.05

typedef struct s_vector2d	t_vector2d;
typedef struct s_game		t_game;

typedef struct s_bbox
{
	t_vector2d	pos;
	t_vector2d	size;
}	t_bbox;

typedef struct s_player
{
	float		hp;
	float		speed;
	float		fov;
	t_vector2d	velocity;
	t_vector2d	dir;
	t_vector2d	pos;
	t_bbox		box;
	int			up;
	int			down;
	int			left;
	int			right;
	int			maj;
	void		(*destroy)(struct s_player *player);
}	t_player;

t_player	*ft_init_player(t_game *game);
void		move_player(t_game	*game);
void		destroy_player(t_player *player);

#endif /* PLAYER_H */
