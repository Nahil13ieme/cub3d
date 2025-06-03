/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:10:44 by nbenhami          #+#    #+#             */
/*   Updated: 2025/05/29 14:18:29 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "cub3d.h"
# include <stdbool.h>

typedef struct s_map				t_map;
typedef struct s_debug				t_debug;
typedef struct s_render				t_render;
typedef struct s_player				t_player;
typedef struct s_texture_manager	t_texture_manager;

typedef struct s_input
{
	bool	w;
	bool	s;
	bool	a;
	bool	d;
	bool	left;
	bool	right;
	bool	maj;
}	t_input;
 
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
	void				*mlx;
	void				*win;
	int					is_debugging;
	char				*files[4];
	t_map				*map;
	t_texture_manager	*tex_man;
	t_debug				*debug;
	t_player			*player;
	t_render			*render;
	t_game_state		game_state;
	t_input				input;
	char				*pathn;
	char				*paths;
	char				*pathw;
	char				*pathe;
	void				(*destroy)(struct s_game *game);
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
