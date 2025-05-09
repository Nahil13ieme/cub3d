/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:30:34 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/17 18:38:05 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
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

int	check_file_name(char *av, int len);
int	check_file(char *av);

# define TRUE 1
# define FALSE 0

# ifndef DEBUG
#  define DEBUG 0
# endif /* DEBUG */

# define W_WIDTH 1080
# define W_HEIGHT 720

#endif /* CUB3D_H */