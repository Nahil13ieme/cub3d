/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:13:49 by tle-saut          #+#    #+#             */
/*   Updated: 2025/06/16 12:44:33 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_input(t_game *game)
{
	game->input.a = false;
	game->input.d = false;
	game->input.w = false;
	game->input.s = false;
	game->input.left = false;
	game->input.right = false;
	game->input.maj = false;
}

void	set_texture_from_path(t_game *game, t_map *map)
{
	set_texture(&game->pathn, map->tab[0]);
	set_texture(&game->paths, map->tab[1]);
	set_texture(&game->pathw, map->tab[2]);
	set_texture(&game->pathe, map->tab[3]);
}
