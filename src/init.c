/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:13:49 by tle-saut          #+#    #+#             */
/*   Updated: 2025/05/30 14:33:51 by tle-saut         ###   ########.fr       */
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
