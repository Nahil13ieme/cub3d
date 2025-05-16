/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:10:34 by nbenhami          #+#    #+#             */
/*   Updated: 2025/05/16 14:35:34 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "cub3d.h"

typedef struct s_vector2d	t_vector2d;
typedef struct s_game		t_game;

typedef struct s_bbox
{
	t_vector2d pos;    // coin en haut à gauche
	t_vector2d size;   // largeur = size.x, hauteur = size.y
} t_bbox;

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
	void		(*destroy)(struct s_player *player);
}	t_player;



t_player	*ft_init_player(t_game *game);
void	apply_velocity(t_game	*game);
void		destroy_player(t_player *player);
void	identify_move(t_game *game);

void	key_pressed(int keycode, t_game *game);
void	key_release(int keycode, t_game *game);

#endif /* PLAYER_H */
