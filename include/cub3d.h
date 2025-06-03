/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/05/30 14:25:44 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <time.h>
# include "vector2d.h"
# include "debug.h"
# include "player.h"
# include "map.h"
# include "texture.h"
# include "raycast.h"
# include "render.h"
# include "game.h"
# include "keys.h"

typedef struct s_bbox		t_bbox;

int			check_file_name(char *av, int len);
int			check_file(char *av);

t_map		*ft_init_map(char *path, t_game *game);
void		init_input(t_game *game);
int			check_border(t_map map);
int			ft_tablen(char	**tab);

void	ft_free_map(char **all);

int		check_collisions(t_bbox player, int rows, int cols);
void	set_player_box(t_player *player);


int	check_cub(t_game *game, t_map *map);


void	free_tab(char **tab);

# define TRUE 1
# define FALSE 0

# define SIZE 64

# define BUFFER_SIZE sizeof(char *)

# ifndef DEBUG
#  define DEBUG 0
# endif /* DEBUG */

# define W_WIDTH 1080
# define W_HEIGHT 720

#endif /* CUB3D_H */
