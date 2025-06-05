/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:51:21 by tle-saut          #+#    #+#             */
/*   Updated: 2025/06/05 14:30:32 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "cub3d.h"

typedef struct s_map				t_map;
typedef struct s_debug				t_debug;
typedef struct s_render				t_render;
typedef struct s_player				t_player;
typedef struct s_texture_manager	t_texture_manager;
typedef struct s_vector2d			t_vector2d;
typedef struct s_game				t_game;
typedef struct s_texture			t_texture;
typedef struct s_raycast			t_raycast;
typedef struct s_bbox				t_bbox;
typedef struct s_render_params		t_render_params;
typedef struct s_wall_params		t_wall_params;
typedef struct s_ray_data			t_ray_data;

/***********************************CHECK_BORDER******************************/
int			check_horizon(char *str);
int			check_verti(char **tab);
int			check_border(t_map map);

/*************************************CHECK_CUB*******************************/
void		copy_map(t_map *map, char **tab, int i);
void		set_texture(char **text, char *str);
int			init_tex_man(t_game *game);
int			check_cub(t_game *game, t_map *map);

/*************************************CHECK_FILE******************************/
int			check_file_name(char *av, int len);
int			check_file(char *av);

/**************************************CHECK_MAP******************************/
char		*ft_strjoinfree(char **s1, char *s2);
char		**ft_init_tab(int fd);
void		ft_print_tab(char **tab);
void		check_size_line(t_map *map);
t_map		*ft_init_map(char *path, t_game *game);

/*************************************COLLISION*******************************/
void		set_player_box(t_player *player);
int			check_collisions(t_bbox player, int rows, int cols);

/************************************DEBUG_UTILS******************************/
long		get_time_microseconds(void);
void		raycast_cone(t_game *game, t_texture *t);

/***************************************DEBUG*********************************/
int			debug_loop(t_debug	*debug);
int			debug_keyhook(int keycode, t_debug *debug);
t_debug		*new_debug(t_game *game);
void		destroy_debug(t_debug **debug);

/**************************************DESTROY********************************/
void		destroy_render(t_render *render);
void		destroy_game(t_game *game);
void		destroy_player(t_player *player);

/****************************************DRAW*********************************/
void		draw_pixel(t_texture *t, int x, int y, int color);
void		draw_line(t_texture *t, t_vector2d start, t_vector2d end,
				int color);
void		init_raycast_vars(t_raycast *ray, t_vector2d origin,
				t_vector2d dir);
int			is_collision(t_raycast *ray, t_game *game);
void		set_side_for_x_bounds(t_raycast *ray);

/**************************************DRAW_2*********************************/
void		set_side_for_y_bounds(t_raycast *ray);
void		set_side_for_wall(t_raycast *ray, int side);
void		set_side_hit(t_raycast *ray, t_game *game, int side);
int			perform_dda(t_game *game, t_raycast *ray);
t_vector2d	raycast_to_wall(t_game *game, t_vector2d origin, t_vector2d dir,
				int *side_hit);

/****************************************GAME*********************************/
t_game		*new_game(void *mlx, void *win, int is_debugging, char **av);
void		input(t_game *game);
int			game_loop(t_game *game);

/***************************************GAME_2********************************/
void		cap_fps(void);
int			handle_key_release(int keycode, t_game *game);
int			key_hook(int keycode, t_game *game);

/****************************************INIT*********************************/
void		init_input(t_game *game);

/****************************************MAP**********************************/
t_map		*new_map(void);
void		destroy_map(t_map *map);
int			parsing(char **tiles);

/***************************************PLAYER********************************/
t_player	*ft_init_player(t_game *game);
void		move_player(t_game *game);

/**************************************RAYCASING******************************/
void		init_wall_rendering(t_game *game, t_render_params *params);
t_texture	*get_wall_texture(t_game *game, int side);
int			calculate_wall_height(double hit_x, double hit_y,
				t_render_params *params, double ray_angle);
void		set_wall_bounds(int wall_height, t_wall_params *wall);
double		calculate_wall_x(t_vector2d hit);

/**************************************RAYCASING_2****************************/
int			is_hit_valid(t_vector2d hit, t_game *game);
void		cast_ray(t_game *game, t_render_params *params,
				int col, t_ray_data *ray);
void		render_wall(t_game *game, t_render_params *params,
				int col, t_ray_data *ray);
void		process_column(t_game *game, t_render_params *params, int col);
void		draw_walls(t_game *game);

/**************************************RAYCASING_3****************************/
void		draw_wall_pixel(t_game *game, t_texture *tex,
				int col, t_wall_params *wall);
int			check_textures(t_game *game);
int			get_texture_color(t_texture *tex, int tex_x, int tex_y);

/****************************************RENDER*******************************/
t_render	*new_render(t_game *game);
void		draw_img_to_buffer(t_texture *b, t_texture *s,
				int x_offset, int y_offset);
void		draw_floor(t_game *game);
void		draw_buffer(t_game *game);

/***************************************RENDER_2******************************/
void		draw_circle(t_texture *t, t_vector2d start, int size, int color);
void		draw_rect(t_texture *t, t_vector2d start, int size, int color);
void		clear_buffer(t_texture *t);
void		draw_debug_buffer(t_game *game);
int			render_loop(t_game *game);

/****************************************TEXTURE******************************/
t_texture	*new_texture_from_file(void *mlx, char *file);
t_texture	*new_texture(void *mlx, int width, int height);
void		load_textures(t_game *game);

/****************************************UTILS********************************/
void		free_tab(char **tab);
int			ft_tablen(char	**tab);

#endif
