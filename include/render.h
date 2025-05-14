/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:42:03 by nbenhami          #+#    #+#             */
/*   Updated: 2025/05/14 12:17:16 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "cub3d.h"

typedef struct s_texture	t_texture;
typedef struct s_vector2d	t_vector2d;
typedef struct s_game		t_game;

typedef struct s_render
{
	void		*mlx;
	t_texture	*main_buffer;
	t_texture	*debug_buffer;
	int			(*render_loop)(struct s_game *game);
	void		(*destroy)(struct s_render *render);
}	t_render;

t_render	*new_render(t_game	*game);
void		draw_buffer(t_game *game);
int			render_loop(t_game *game);
void		destroy_render(t_render *render);
void		draw_pixel(t_texture *t, int x, int y, int color);
void		draw_thick_pixel(t_texture *t, int x, int y, int size, int color);
void		draw_line(t_texture *t, t_vector2d start, t_vector2d end, int size);

#endif /* RENDER_H */