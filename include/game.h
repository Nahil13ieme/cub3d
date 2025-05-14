/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:10:44 by nbenhami          #+#    #+#             */
/*   Updated: 2025/05/14 11:55:41 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "cub3d.h"

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

typedef struct s_map	t_map;
typedef struct s_debug	t_debug;
typedef struct s_render	t_render;
typedef struct s_player	t_player;

typedef enum e_game_state
{
	NONE,
	RUNNING,
	PAUSED,
	DIED,
	EXITING
}	t_game_state;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	int				is_debugging;
	t_map			*map;
	t_debug			*debug;
	t_player		*player;
	t_render		*render;
	t_game_state	game_state;
	void			(*destroy)(struct s_game *game);
}	t_game;

enum e_fps
{
	FRAME_TIME_MS = (1000 / 60)
};

t_game	*new_game(void *mlx, void *win, int is_debugging, char **av);

int		game_loop(t_game *game);

void	cap_fps(void);

void	destroy_game(t_game *game);

int		key_hook(int keycode, t_game *game);
int		handle_key_release(int keycode, t_game *game);

#endif /* GAME_H */
