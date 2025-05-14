/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/05/14 14:13:17 by nbenhami         ###   ########.fr       */
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
# include "render.h"
# include "game.h"

int			check_file_name(char *av, int len);
int			check_file(char *av);

t_map		*ft_init_map(char *path);
t_player	*ft_init_player(char **map);
int			check_border(t_map map);

# define TRUE 1
# define FALSE 0

# define BUFFER_SIZE sizeof(char *)

# ifndef DEBUG
#  define DEBUG 0
# endif /* DEBUG */

# define W_WIDTH 1080
# define W_HEIGHT 720

#endif /* CUB3D_H */
