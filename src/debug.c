/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:09:00 by nbenhami          #+#    #+#             */
/*   Updated: 2025/06/03 06:17:51 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/debug.h"

int	debug_loop(t_debug	*debug)
{
	(void)debug;
	printf("test\n");
	return (0);
}

int	debug_keyhook(int keycode, t_debug *debug)
{
	if (keycode == 65307)
		debug->destroy(&debug);
	return (0);
}

t_debug	*new_debug(t_game *game)
{
	t_debug	*debug;

	debug = malloc(sizeof(t_debug));
	if (!debug)
	{
		printf("Malloc error, what did you do ??");
		exit(EXIT_FAILURE);
	}
	debug->mlx = game->mlx;
	debug->win = mlx_new_window(debug->mlx, (game->map->width + 1) * 32,
			(game->map->height + 1) * 32, "debug_window");
	debug->game = game;
	debug->destroy = destroy_debug;
	mlx_hook(debug->win, 2, 1L << 0, debug_keyhook, debug);
	return (debug);
}

void	destroy_debug(t_debug **debug)
{
	if (!(*debug))
		return ;
	(*debug)->game->is_debugging = 0;
	mlx_destroy_window((*debug)->mlx, (*debug)->win);
	(*debug)->win = NULL;
	free((*debug));
	(*debug) = NULL;
}
