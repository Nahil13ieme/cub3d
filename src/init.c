/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:13:49 by tle-saut          #+#    #+#             */
/*   Updated: 2025/05/22 17:08:54 by nbenhami         ###   ########.fr       */
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
}